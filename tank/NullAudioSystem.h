#ifndef NULL_AUDIO_SYSTEM_H
#define NULL_AUDIO_SYSTEM_H


#include "IAudioSystem.h"


class NullAudioSystem : public IAudioSystem
{
public:
   NullAudioSystem();
   ~NullAudioSystem();

   virtual bool initialize(const char* device, const char* parameters);
   virtual bool play(const char* filename);
   virtual bool playMusic(const char* filename);
};


#endif
