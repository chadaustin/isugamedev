#ifndef I_AUDIO_SYSTEM_H
#define I_AUDIO_SYSTEM_H


// this sucks
class IAudioSystem
{
public:
   virtual ~IAudioSystem() { };
   virtual bool initialize(const char* device, const char* parameters) = 0;
   virtual bool play(const char* filename) = 0;
};


#endif
