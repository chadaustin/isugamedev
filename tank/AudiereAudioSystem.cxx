#include "AudiereAudioSystem.h"


AudiereAudioSystem::AudiereAudioSystem()
{
   m_current_stream = 0;
}


bool
AudiereAudioSystem::initialize(const char* device, const char* parameters)
{
   m_context = audiere::OpenDevice();
   return bool(m_context);
}


bool
AudiereAudioSystem::play(const char* filename)
{
   if (!m_context) {
      return false;
   }

   // try to open a new stream
   m_streams[m_current_stream] = audiere::OpenSound(m_context.get(), filename);
   if (m_streams[m_current_stream]) {
      m_streams[m_current_stream]->play();
      m_current_stream = (m_current_stream + 1) % MAX_SOUND_EFFECTS;
      return true;
   } else {
      return false;
   }
}

bool
AudiereAudioSystem::playMusic(const char* filename)
{
   if (!m_context) {
      return false;
   }

   m_background_music = audiere::OpenSound(m_context.get(), filename, true);
   if (m_background_music) {
      m_background_music->setRepeat(true);
      m_background_music->setVolume(0.1f);
      m_background_music->play();
      return true;

   } else {
      return false;
   }
}
