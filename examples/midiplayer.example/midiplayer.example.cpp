
// MIDI player example
//
// - demo by Kevin Meinert <kevin@vrsource.org>
//
// - Demonstrates how to
//   - abstract a MIDI output interface
//   - control MIDI in Win32 through example Win32Midi implementation
//   - write a MIDI Sequencer using discrete events (synced on a MIDI clock)
//   - read binary data from a midi file into the Sequencer
//   - deal with endian issues
//   - use these components to make a simple MIDI file player.
//
// - TODO:
//   - Implement MIDI events for msgs other than progchange, and note
//     Background: The only events actually queued are program change, and 
//     note messages other midi events cannot be ignored, and thus have dummy 
//     events queued for them to keep the timing sane.  Omission of any event
//     can throw off the timing of an entire piece, simply because every
//     event is stored as a delta in the MIDI file.
//   - add interface(s) for all events to the Midi classes
//   - correctly implement timing in sequencer based on values read from 
//     midi file.  (currently plays too fast)
//

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <list>

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
// Midi abstraction(s)
// If you need one for your platform, simply use the same interface, 
// and type def your class to "Midi"
///////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

   /* an implementation of the "Midi" type for Win32 platform
    * (see below for the "typedef win32midi midi" line)
    * Usage:
    *   Midi m;
    *   m.open(); 
    *   m.trigger();
    *   m.close();
    *
    * references:
    * http://msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/midi_3fqr.asp
    * http://www.borg.com/~jglatt/tech/lowmidi.htm
    */
   class Win32Midi
   {
   public:
      /* open the midi device
       * this must be called prior to any other functions in this class 
       */
      virtual void open()
      {
         unsigned long result;
      
         /* Open the MIDI Mapper */
         result = midiOutOpen(&mHandle, (UINT)-1, (DWORD)MidiOutProc, (DWORD)this, CALLBACK_FUNCTION);
         if (result)
         {
            printf("There was an error opening MIDI Mapper!\r\n");
         }

      }

      /* trigger the midi note, on channel, with velocity */
      virtual void trigger( char note, char channel = 0x0, char velocity = 0x40 )
      {
         int chan_nibble = (0x0f & channel); // only lower nibble is recognized.
         int trig_nibble = 0x90; // trigger is 9, where X is the chan
         int status = trig_nibble | chan_nibble; // 

         int msg = (velocity << 16) | (note << 8) | status;

         midiOutShortMsg(mHandle, msg);
      }

      /* release the midi note, velocity is ignored and should be 0 */
      virtual void release( char note, char channel = 0x0, char velocity = 0x00 )
      {
         int chan_nibble = (0x0f & channel); // only lower nibble is recognized.
         int trig_nibble = 0x80; // trigger is 9, where X is the chan
         int status = trig_nibble | chan_nibble; // 

         velocity = 0;
         int msg = (velocity << 16) | (note << 8) | status;
      
         midiOutShortMsg(mHandle, msg);
      }

      /* just play a note, then release. */
      virtual void playnote( char note, char channel = 0x0, char velocity = 0x40, int duration_millisec = 100 )
      {
         this->trigger( note, channel, velocity );
         Sleep( duration_millisec );
         this->release( note, channel );
      }

      /* change the instrument on a given channel */
      virtual void programchange( char program, char channel = 0x0 )
      {
         int chan_nibble = (0x0f & channel); // only lower nibble is recognized.
         int progchange_nibble = 0xC0; // trigger is 9, where X is the chan
         int status = progchange_nibble | chan_nibble; // 

         int msg = (program << 8) | status;

         midiOutShortMsg(mHandle, msg);
      }

      /* close the midi device. */
      virtual void close()
      {
         unsigned long result;
         /* Open the MIDI Mapper */
         result = midiOutClose( mHandle );
         if (result)
         {
            printf("There was an error closing MIDI Mapper!\r\n");
         }

      }

      /* print to stdout the midi input devices on your win32 system.. */
      virtual void printInDevices()
      {
         MIDIINCAPS     mic;
         unsigned long    iNumDevs, i;

         /* Get the number of MIDI In devices in this computer */
         iNumDevs = midiInGetNumDevs();

         /* Go through all of those devices, displaying their names */
         for (i = 0; i < iNumDevs; i++)
         {
             /* Get info about the next device */
             if (!midiInGetDevCaps(i, &mic, sizeof(MIDIINCAPS)))
             {
                 /* Display its Device ID and name */
                 printf("Device ID #%u: %s\r\n", i, mic.szPname);
             }
         }

      }

      /* print to stdout the midi output devices on your win32 system.. */
      virtual void printOutDevices()
      {
         MIDIOUTCAPS     moc;
         unsigned long   iNumDevs, i;

         /* Get the number of MIDI Out devices in this computer */
         iNumDevs = midiOutGetNumDevs();

         /* Go through all of those devices, displaying their names */
         for (i = 0; i < iNumDevs; i++)
         {
             /* Get info about the next device */
             if (!midiOutGetDevCaps(i, &moc, sizeof(MIDIOUTCAPS)))
             {
                 /* Display its Device ID and name */
                 printf("Device ID #%u: %s\r\n", i, moc.szPname);
             }
         }
      }

   protected:
      /* This function is called on all Win32 midi messages
       */
      virtual void callback( UINT wMsg )
      {
         //printf("virtual Callback happened!\n");
      }
   private:
      static void CALLBACK MidiOutProc(
        HMIDIOUT hmo,      
        UINT wMsg,         
        DWORD dwInstance,  
        DWORD dwParam1,    
        DWORD dwParam2     
      )
      {
         Win32Midi* ths = reinterpret_cast<Win32Midi*>( dwInstance );
         ths->callback( wMsg );
      }

      HMIDIOUT  mHandle;
   };

   // under win32, our "Midi" class is the Win32Midi class...
   typedef Win32Midi Midi;
#else
   "ERROR: the Midi type is not able to be defined"
#endif


///////////////////////////////////////////////////////////////////////////////
// MIDI Sequencer
///////////////////////////////////////////////////////////////////////////////


/* a generic sequencer event, does nothing, and 
 * serves as a base class for all events 
 */
class Event
{
public:
   Event()
   {
   }
   virtual void exec( Midi& m ) {};
};

// Event sequencer
// TODO: the timing may not be calculated correctly (or even specifiable completely) 
class Sequencer
{
public:
   /* default constructor
    */
   Sequencer() : mTickTime( 0.08232f ), mBpm( 120.0f ), mPPQN( 4.0f )
   {
   }

   /* provide the absolute (not delta) time (in ticks) that the event is to be triggered
    */
   void addEvent( int ticks, Event* event )
   {
      mEvents[ticks].push_back( event );
   }

   /* run the sequenced event list
    * this function blocks until finished
    */
   void run( Midi& m )
   {
      // as we iterate over each time slot, we then execute all the events for that slot.
      
      int old_ticks = 0;
      float msec_per_tick = mTickTime * 1000.0f;
      
      // for each time slot
      std::map<int, std::list<Event*> >::iterator map_itr;
      for (map_itr = mEvents.begin(); map_itr != mEvents.end(); ++map_itr)
      {
         // execute the number of midi clock ticks between events.
         int delta_ticks = (*map_itr).first - old_ticks;
         old_ticks = (*map_itr).first;
         for (int x = 0; x < delta_ticks; ++x)
         {
            this->tick( msec_per_tick );
         }     
         
         // execute each event in current time slot (can be 1 to n).
         std::list<Event*>& event_list = (*map_itr).second; // an alias to the list
         std::list<Event*>::iterator list_itr;
         for (list_itr = event_list.begin(); list_itr != event_list.end(); ++list_itr)
         {
            (*list_itr)->exec( m );
         }
      }
   }

   /* set explicitly the amount of time in one midi clock
    */
   void setTickTime( float sec )
   {
      mTickTime = sec;
      
   }

   /* function that is called on each midi clock tick 
    * if you overload, make sure you sleep for dt, or call this function 
    */
   virtual void tick( float dt )
   {
      Sleep( dt );
   }

   /* set the number of pulses per quarter note */
   void setPPQN( float ppqn )
   {
      mPPQN = ppqn;
      this->updateBpmPPQN();
   }

   /* set the tempo in beats per minute */
   void setBpm( float bpm )
   {
      mBpm = bpm;
      this->updateBpmPPQN();
   }

   /* fps is one of the 4 SMPTE standards representing frames per second 24, 25, 29, or 30
    * resolution is the number of subframes (clock ticks) in each frame
    */
   void setSMPTE( char fps, char resolution )
   {
      float tick_per_sec = (float)fps * (float)resolution;
      float sec_per_tick = 1.0f / tick_per_sec;
      this->setTickTime( sec_per_tick );
   }

private:
   /* called whenever bpm or ppqn is updated
    */
   void updateBpmPPQN()
   {
      float beat_per_sec = mBpm * (1.0f/60.0f);
      float tick_per_sec = beat_per_sec * mPPQN;
      float sec_per_tick = 1.0f / tick_per_sec;
      //float msec_per_tick = sec_per_tick * 1000.0f;

      this->setTickTime( sec_per_tick );

      //std::cout << "- time:" << sec_per_tick << " ppqn:" << mPPQN << " bpm:" 
      //          << mBpm << "\n" << std::flush;
            
   }
   float mBpm, mPPQN, mTickTime;

   // this gives the sequencer the ability for each time slot to have multiple events.
   // as we iterate over each time slot, we then execute all the events for that slot.
   std::map<int, std::list<Event*> > mEvents;
};

/* midi trigger or release
 * sequencer event 
 */
class NoteEvent : public Event
{
public:
   NoteEvent() : note( 60 ), velocity( 0x40 ), channel( 0 )
   {
   }
   virtual void exec( Midi& m )
   {
      if (trigger)
         m.trigger( note, channel, velocity );
      else 
         m.release( note, channel );

      std::cout << "trigger: note(" << note 
                << ") chan(" << channel << ") vel("
                << velocity << ")\n" << std::flush;
   }
   int note, velocity, channel;
   bool trigger;
};

/* midi program (instrument) change
 * sequencer event 
 */
class ProgramChangeEvent : public Event
{
public:
   ProgramChangeEvent() : prognum( 0 ), channel( 0 )
   {
   }
   virtual void exec( Midi& m )
   {
      std::cout << "program change: prog(" << prognum 
                << ") chan(" << channel << ")\n" << std::flush;
      m.programchange( prognum, channel );
   }
   int prognum, channel;
};



///////////////////////////////////////////////////////////////////////////////
// Endian support 
// (MIDI uses a lot of big endian data, 
//  on Intel we need to reverse the bytes in that data)
///////////////////////////////////////////////////////////////////////////////

namespace kev
{

   //: Swap the bytes in any data type.
   // Motorola and Intel store their bytes in reversed formats <BR>
   // ex: An SGI image is native to the SGI system,            <BR>
   // to be read on an intel machine, it's bytes need to be reversed <BR>
   // NOTE: chars aren't affected by this since it only        <BR>
   // affects the order of bytes, not bits.
   template< class Type >
   inline void  byteReverse(Type& bytes)
   {       
       const int size = sizeof(Type);
       Type buf = 0;
       int x, y;

       //we want to index the bytes in the buffer
       unsigned char* buffer = (unsigned char*) &buf;

       for ( x = 0, y = size-1; 
                  x < size;
                  ++x, --y )
       {
         buffer[x] |= ((unsigned char*)&bytes)[y];
       }
       bytes = buf;
   }

   //: check the system for endianess
   inline bool isLittleEndian() 
   {
      union 
      {
         short   val;
         char    ch[sizeof(short)];
      } un;

      // initialize the memory that we'll probe
      un.val = 256;       // 0x10

      // If the 1 byte is in the low-order position (un.ch[1]), this is a
      // little-endian system.  Otherwise, it is a big-endian system.
      return un.ch[1] == 1;
   }

   //: check the system for endianess
   inline bool isBigEndian()
   {
      return !isLittleEndian();
   }   
}

///////////////////////////////////////////////////////////////////////////////
// MIDI file loader
///////////////////////////////////////////////////////////////////////////////

struct CHUNK_HEADER
{
   char           ID[4];
   unsigned long  Length;
};

struct MTHD_CHUNK
{
   /* Here's the 8 byte header that all chunks must have */
   char           ID[4];  /* This will be 'M','T','h','d' */
   unsigned long  Length; /* This will be 6 */

   /* Here are the 6 bytes */
   unsigned short Format;
   unsigned short NumTracks;
   unsigned short Division;
};

// An MTrk chunk contains all of the midi data (with timing bytes), 
// plus optional non-midi data for one track. Obviously, you should 
// encounter as many MTrk chunks in the file as the MThd chunk's 
// NumTracks field indicated. 
struct MTRK_CHUNK
{
   /* Here's the 8 byte header that all chunks must have */
   char           ID[4];   /* This will be 'M','T','r','k' */
   unsigned long  Length;  /* This will be the actual size of Data[] */

   /* Here are the data bytes */
   unsigned char  Data[1];  /* Its actual size is Data[Length] */
};


void WriteVarLen( std::ofstream& f, unsigned long value )
{
   unsigned long buffer = 0;
   buffer = value & 0x7F;

   while ( (value >>= 7) )
   {
     buffer <<= 8;
     buffer |= ((value & 0x7F) | 0x80);
   }

   while (TRUE)
   {
      f.write( (const char*)&buffer, 1 );
      //putc(buffer,outfile);
      if (buffer & 0x80)
          buffer >>= 8;
      else
          break;
   }
}

unsigned long ReadVarLen( std::ifstream& f )
{
    unsigned long value = 0;
    unsigned char c = 0;

    f.read( (char*)&value, 1 );
    //value = getc(infile);
    if ( value & 0x80 )
    {
       value &= 0x7F;
       do
       {
         //c = getc(infile);
         f.read( (char*)&c, 1 );
         value = (value << 7) + (c & 0x7F);
       } while (c & 0x80);
    }

    return(value);
}

/* load a midi file, into a Sequencer object 
 *
 * References:
 *  http://www.borg.com/~jglatt/tech/midifile.htm
 *  http://www.borg.com/~jglatt/tech/midispec.htm
 */
void loadMidFile( Sequencer& s, const std::string& filename )
{
   std::ifstream f;
   f.open( filename.c_str(), std::ios::in | std::ios::binary );

   int midi_tracks = 1;
   unsigned short format, numtracks, division;
   
   // in midi file, time stamps are relative (deltas)
   // in the seq class (sequencer), time stamps are absolute
   // use this array of 16 to accumulate the deltas read from the midi file.
   // the accumulated delta on tick[x] is the absolute value we will give the seq class...
   // the added benefit of this is that it will mix all channels in a midi file together for us.
   int ticks[16];
   for (int x = 0; x < 16; ++x)
      ticks[x] = 0;
         
   // while there is stuff to read...
   while (!f.eof())
   {
      CHUNK_HEADER header;
      f.read( (char*)&header, sizeof( CHUNK_HEADER ) );

      // bail if we're at eof now, this happens sometimes 
      // if there is extra data in the file...
      if (f.eof())
         continue;

      
      // get the number of bytes left in the chunk
      if (kev::isLittleEndian())
         kev::byteReverse( header.Length );

      // debug output...
      // std::cout << "type: " << header.ID[0] << " " << header.ID[1] << " " << header.ID[2] 
      //           << " " << header.ID[3] << "\n" << std::flush;
      // std::cout << "len:  " << header.Length << "\n" << std::flush;
   
      // header chunk, all midi files have this..
      if (header.ID[0] == 'M' && header.ID[1] == 'T' && 
          header.ID[2] == 'h' && header.ID[3] == 'd')
      {
         f.read( (char*)&format, sizeof( unsigned short ) );
         f.read( (char*)&numtracks, sizeof( unsigned short ) );
         f.read( (char*)&division, sizeof( unsigned short ) );
         if (kev::isLittleEndian())
         {
            kev::byteReverse( format );
            kev::byteReverse( numtracks );
            kev::byteReverse( division );
         }

         // std::cout << "Format: " << format << "\n" << std::flush;
         // std::cout << "Numtracks: " << numtracks << "\n" << std::flush;
         // std::cout << "Division (pulses per quarternote): " << division << " "
         //           << (int)((char*)&division)[0] << "," << (int)((char*)&division)[1] 
         //           << "\n" << std::flush;

         // set up seq
         s.setPPQN( division );
      }

      // An MTrk chunk contains all of the midi data (with timing bytes), 
      // plus optional non-midi data for one track. Obviously, you should 
      // encounter as many MTrk chunks in the file as the MThd chunk's 
      // NumTracks field indicated. 
      else if (header.ID[0] == 'M' && header.ID[1] == 'T' &&
               header.ID[2] == 'r' && header.ID[3] == 'k')
      {
         bool done = false;
         unsigned char  saved_status = 0;
         while (done == false && !f.eof())
         {
            unsigned long delta_time = ReadVarLen( f );
            //if (kev::isLittleEndian())
            //   kev::byteReverse( delta_time );

            //std::cout<<"delta_time: " << delta_time << "\n"<<std::flush;
         

            unsigned char midi_event = 0;
            f.read( (char*)&midi_event, 1 );
            
            //printf( "midi_event: %x\n", (char)midi_event );

running_status_jump_point:
            // note on event (two data bytes follow the status) 
            if (((midi_event & 0xf0) == 0x90) || ((midi_event & 0xf0) == 0x80))
            {
               unsigned char note, velocity;
               f.read( (char*)&note, 1 );
               f.read( (char*)&velocity, 1 );
         
               NoteEvent* event = new NoteEvent;
               event->note = note & 0x7f;
               event->velocity = velocity & 0x7f;
               event->trigger = ((midi_event & 0xf0) == 0x90) && (event->velocity > 0);
               event->channel = midi_event & 0x0f;
               ticks[event->channel] += delta_time;
               s.addEvent( ticks[event->channel], event );
               
               //std::cout<<"note ("<<event->trigger<<"): " << (int)note << " " 
               //         << (int)velocity <<"\n"<<std::flush;
            }

            // aftertouch
            else if ((midi_event & 0xf0) == 0xA0)
            {
               unsigned char note, velocity;
               f.read( (char*)&note, 1 );
               f.read( (char*)&velocity, 1 );

               // add (dummy) event to sequencer 
               int channel = midi_event & 0x0f;
               ticks[channel] += delta_time;
               s.addEvent( ticks[channel], new Event );
            }

            // control change
            else if ((midi_event & 0xf0) == 0xb0)
            {
               unsigned char controller, value;
               f.read( (char*)&controller, 1 );
               f.read( (char*)&value, 1 );

               // add (dummy) event to sequencer 
               int channel = midi_event & 0x0f;
               ticks[channel] += delta_time;
               s.addEvent( ticks[channel], new Event );
            }

            // program change
            else if ((midi_event & 0xf0) == 0xC0)
            {
               unsigned char prog_num;
               f.read( (char*)&prog_num, 1 );

               // add (dummy) event to sequencer 
               ProgramChangeEvent* event = new ProgramChangeEvent;
               event->channel = midi_event & 0x0f;
               event->prognum = prog_num;
               ticks[event->channel] += delta_time;
               s.addEvent( ticks[event->channel], event );

               //std::cout<<"progchange ("<<event->prognum<<"): chan (" << (int)event->channel 
               //         << ") ticks("<<ticks[event->channel]<<")\n"<<std::flush;
            }

            // channel pressure
            else if ((midi_event & 0xf0) == 0xD0)
            {
               unsigned char pressure_amount;
               f.read( (char*)&pressure_amount, 1 );

               // add (dummy) event to sequencer 
               int channel = midi_event & 0x0f;
               ticks[channel] += delta_time;
               s.addEvent( ticks[channel], new Event );
            }

            // pitch wheel
            else if ((midi_event & 0xf0) == 0xE0)
            {
               unsigned char part1, part2;
               f.read( (char*)&part1, 1 );
               f.read( (char*)&part2, 1 );

               // add (dummy) event to sequencer 
               int channel = midi_event & 0x0f;
               ticks[channel] += delta_time;
               s.addEvent( ticks[channel], new Event );
            }

            // system exclusive
            else if (midi_event == 0xF0)
            {
               unsigned char note = 0xf0;
               while (note != 0xf7) // throw away the data...
               {
                  f.read( (char*)&note, 1 );
               }
            }

            // MTC Quarter Frame Message
            else if (midi_event == 0xf1)
            {
               unsigned char time_code;
               f.read( (char*)&time_code, 1 );
            }

            
            // Song Position Pointer
            else if (midi_event == 0xf2)
            {
               unsigned char part1, part2;
               f.read( (char*)&part1, 1 );
               f.read( (char*)&part2, 1 );
            }

            // Song Select
            else if (midi_event == 0xf3)
            {
               unsigned char part1;
               f.read( (char*)&part1, 1 );
            }

            // tune request (ask the device to tune itself)
            else if (midi_event == 0xf6)
            {
               // no data.
            }

            // midi clock
            else if (midi_event == 0xf8)
            {
               // no data.
            }

            // tick
            else if (midi_event == 0xf9)
            {
               // no data.
            }

            // midi start
            else if (midi_event == 0xfa)
            {
               // no data.
            }

            // midi continue
            else if (midi_event == 0xfb)
            {
               // no data.
            }

            // midi stop
            else if (midi_event == 0xfc)
            {
               // no data.
            }

            // active sense
            else if (midi_event == 0xfe)
            {
               // no data.
            }

            // midi reset
            //else if (midi_event == 0xff)
            //{
               // no data.
            //}

            // ignore these undefined msgs
            else if (midi_event == 0xF4 ||
                     midi_event == 0xF5 ||
                     midi_event == 0xF9 ||
                     midi_event == 0xFD)
            {
               // no data.
            }

            // meta event
            else if (midi_event == 0xFF)
            {
               unsigned char type = 0;
               f.read( (char*)&type, 1 );

               // end of track event
               if (type == 0x2F)
               {
                  done = true;
                  unsigned long data_len = ReadVarLen( f ); // should be 0, no data
               }

               // tempo 
               else if (type == 0x51)
               {
                  unsigned long data_len = ReadVarLen( f );
                  unsigned long high = 0, med = 0, low = 0;
                  f.read( (char*)&high, 1 );
                  f.read( (char*)&med, 1 );
                  f.read( (char*)&low, 1 );
                  unsigned long microsecs_per_quarter_note = (high << 16) | (med << 8) | low;
               }

               else
               {
                  unsigned long data_len = ReadVarLen( f );
                  
                  // throw away the meta event data...
                  std::string data;
                  data.resize( data_len );
                  f.read( (char*)&data[0], data.size() );

                  //std::cout<<"meta event: "<<data_len<<"\n"<<std::flush;
               }
         
            }

            // running staus case (use the last status message)
            else
            {
               f.putback( midi_event );
               midi_event = saved_status;
               goto running_status_jump_point;
            }

            saved_status = midi_event;
         }
      }

      // unknown chunk type, read the data and throw it out...
      else
      {
         std::string data;
         data.resize( header.Length );
         f.read( (char*)&data[0], data.size() );
      }

   }

   f.close();
}


///////////////////////////////////////////////////////////////////////////////
// Simple Midi File Player (executable)
///////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
   std::string arg = "midiplayer.example.mid";
   if (argc == 2)
      arg = argv[1];


   Midi m;
   Sequencer seq;
   m.open();
   loadMidFile( seq, arg.c_str() );
   seq.run( m );
   m.close();

   return 0;
}