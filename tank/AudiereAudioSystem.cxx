#include "AudiereAudioSystem.h"


AudiereAudioSystem::AudiereAudioSystem()
{
   m_context = 0;
   for (int i = 0; i < MAX_SOUND_EFFECTS; i++) {
      m_streams[i] = 0;
   }
   m_current_stream = 0;
   m_background_music = 0;
}


AudiereAudioSystem::~AudiereAudioSystem()
{
   // destroy the streams
   for (int i = 0; i < MAX_SOUND_EFFECTS; i++) {
      if (m_streams[i]) {
         AdrCloseStream(m_streams[i]);
         m_streams[i] = 0;
      }
   }

   // destroy the background music
   if (m_background_music) {
      AdrCloseStream(m_background_music);
      m_background_music = 0;
   }

   AdrDestroyContext(m_context);
}


bool
AudiereAudioSystem::initialize(const char* device, const char* parameters)
{
   m_context = AdrCreateContext(
      device, parameters,
      0, 0, 0, 0, 0, 0
   );
   return (m_context != 0);
}


bool
AudiereAudioSystem::play(const char* filename)
{
   if (!m_context) {
      return false;
   }

   // close the current stream
   if (m_streams[m_current_stream]) {
      AdrCloseStream(m_streams[m_current_stream]);
      m_streams[m_current_stream] = 0;
   }

   // try to open a new stream
   m_streams[m_current_stream] = AdrOpenStream(m_context, filename);
   if (m_streams[m_current_stream]) {
      AdrPlayStream(m_streams[m_current_stream]);
      m_current_stream = (m_current_stream + 1) % MAX_SOUND_EFFECTS;
      return true;
   } else {
      return false;
   }
}


bool
AudiereAudioSystem::playMusic(const char* filename)
{
   if (m_background_music) {
      AdrCloseStream(m_background_music);
      m_background_music = 0;
   }

   m_background_music = AdrOpenStream(m_context, filename);
   if (m_background_music) {

      AdrSetStreamRepeat(m_background_music, ADR_TRUE);
      AdrPlayStream(m_background_music);
      return true;

   } else {
      return false;
   }
}
