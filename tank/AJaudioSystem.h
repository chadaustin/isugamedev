#ifndef AJ_AUDIO
#define AJ_AUDIO

#include "IAudioSystem.h"

// this sucks
class AJaudioSystem : public IAudioSystem
{
public:
   virtual ~AJaudioSystem() { };

   // pass in "" for device and "" for parameters for now  ;)
   // eventually, we may want to differentiate between openal output and
   // /dev/dsp output or something
   virtual bool initialize(const char* device, const char* parameters);

   // returns true if the song played successfully, and false otherwise
   virtual bool play(const char* filename);

   // returns true if music started successfully, false otherwise
   virtual bool playMusic(const char* filename);
};


#endif
