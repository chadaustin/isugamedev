#ifndef NULL_AUDIO_SYSTEM_H
#define NULL_AUDIO_SYSTEM_H


#include "IAudioSystem.h"


class NullAudioSystem : public IAudioSystem
{
public:
   NullAudioSystem();
   ~NullAudioSystem();

   bool initialize(const char* device, const char* parameters);
   bool play(const char* filename);
};


#endif
