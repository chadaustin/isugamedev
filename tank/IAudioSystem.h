#ifndef I_AUDIO_SYSTEM_H
#define I_AUDIO_SYSTEM_H


// this sucks
class IAudioSystem
{
public:
   virtual ~IAudioSystem() { };

   // pass in "" for device and "" for parameters for now  ;)
   // eventually, we may want to differentiate between openal output and
   // /dev/dsp output or something
   virtual bool initialize(const char* device, const char* parameters) = 0;

   // returns true if the song played successfully, and false otherwise
   virtual bool play(const char* filename) = 0;
};


#endif
