#ifndef AUDIERE_AUDIO_SYSTEM_H
#define AUDIERE_AUDIO_SYSTEM_H


#include <audiere.h>
#include "IAudioSystem.h"


class AudiereAudioSystem : public IAudioSystem
{
public:
   AudiereAudioSystem();
   ~AudiereAudioSystem();

   virtual bool initialize(const char* device, const char* parameters);
   virtual bool play(const char* filename);
   virtual bool playMusic(const char* filename);

private:
   // we just need a comment
   enum { MAX_SOUND_EFFECTS = 16 };

   ADR_CONTEXT m_context;
   ADR_STREAM m_streams[MAX_SOUND_EFFECTS];
   int m_current_stream;
   ADR_STREAM m_background_music;
};


#endif
