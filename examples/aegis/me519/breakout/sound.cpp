#include "sound.hpp"


SoundEngine g_sound_engine;


void
SoundEngine::playSound(const char* filename) {
  // ensure that a context exists
  if (!m_device) {
    m_device = audiere::OpenDevice();
    if (!m_device) {
      return;
    }
  }

  audiere::SoundEffectPtr stream = m_streams[filename];
  if (!stream) {
    stream = audiere::OpenSoundEffect(
      m_device.get(),
      filename,
      audiere::MULTIPLE);
    m_streams[filename] = stream;
  }
  if (stream) {
    stream->play();
  }
}
