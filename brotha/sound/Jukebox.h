#ifndef SOUND_JUKEBOX_H
#define SOUND_JUKEBOX_H


#include <vector>
#include <string>
#include <audiere.h>


namespace sound {

   class Jukebox {
   public:
      /**
       * The Jukebox uses a specified context to create audio streams.
       */
      Jukebox(audiere::Context* context);

      ~Jukebox();

      /**
       * Return current size of playlist.
       */
      int getTrackCount();

      /**
       * Return the filename at position index.
       */
      std::string getTrack(int index);

      /**
       * Append a sound filename to the end of the playlist.
       */
      void addTrack(const std::string& track);

      /**
       * Remove the track from the playlist if it exists.  Otherwise, do
       * nothing.
       */
      void removeTrack(const std::string& track);

      /**
       * Remove the track at position index from the playlist.
       */
      void removeTrack(int index);

      /**
       * Start playing tracks sequentially from the jukebox.
       */
      void play();

      /**
       * Tell Jukebox to stop playing sound.
       */
      void stop();

      /**
       * Updates the jukebox, moving to the next song if necessary.
       *
       * Call this once every frame or so.
       */
      void update();

   private:
      void tryOpenTrack();
      void nextTrack();

      audiere::Context* mContext;
      std::vector<std::string> mTracks;

      int mCurrentIndex;
      audiere::Stream* mCurrentTrack;
      bool mIsPlaying;
   };

}


#endif
