#ifndef SOUND_HPP
#define SOUND_HPP


// VC++ 6 sucks
#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif


#include <map>
#include <string>
#include <audiere.h>


struct SoundEngine {
  SoundEngine();
  ~SoundEngine();

  void playSound(const char* filename);

private:
  typedef std::map<std::string, audiere::Stream*> StreamMap;

  audiere::Context* m_context;
  StreamMap m_streams;
  int m_next_sound;
};


extern SoundEngine g_sound_engine;


#endif
