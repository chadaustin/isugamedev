#include "sound.hpp"


SoundEngine g_sound_engine;


SoundEngine::SoundEngine() {
  m_next_sound = 0;
}


SoundEngine::~SoundEngine() {
  StreamMap::iterator i = m_streams.begin();
  for (; i != m_streams.end(); ++i) {
    delete i->second;
  }
  m_streams.clear();

  delete m_context;
}


void
SoundEngine::playSound(const char* filename) {
  // ensure that a context exists
  if (!m_context) {
    m_context = audiere::CreateContext();
    if (!m_context) {
      return;
    }
  }

  if (m_streams.count(filename)) {
    m_streams[filename]->play();
  } else {
    audiere::Stream* stream = m_context->openStream(filename);
    if (stream) {
      m_streams[filename] = stream;
      stream->play();
    }
  }
}
