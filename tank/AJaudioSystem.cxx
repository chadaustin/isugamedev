
#include <aj/AudioJuggler.h> // AJ api
#include "AJaudioSystem.h"

// pass in "" for device and "" for parameters for now  ;)
// eventually, we may want to differentiate between openal output and
// /dev/dsp output or something
bool AJaudioSystem::initialize(const char* device, const char* parameters)
{
   aj::SoundAPIInfo sai;
   AudioJuggler::instance().configure( sai );
   AudioJuggler::instance().changeAPI( "OpenAL" );
   return true;
}

// returns true if the song played successfully, and false otherwise
bool AJaudioSystem::play(const char* filename)
{
   std::string alias = filename;// no other name supplied for the handle
   aj::SoundInfo desc;
   desc.filename = filename;
   desc.ambient = false;
   desc.retriggerable = true;
   desc.repeat = 1;
   desc.position.set( 0,0,0 ); // TODO: this function needs to take a pos
   AudioJuggler::instance().configure( alias, desc );
   return true;
}

// returns true if music started successfully, false otherwise
bool AJaudioSystem::playMusic(const char* filename)
{
   std::string alias = filename;// no other name supplied for the handle
   aj::SoundInfo desc;
   desc.filename = filename;
   desc.ambient = true;
   desc.retriggerable = false;
   desc.repeat = -1;
   desc.position.set( 0,0,0 );
   AudioJuggler::instance().configure( alias, desc );
   return true;
}
