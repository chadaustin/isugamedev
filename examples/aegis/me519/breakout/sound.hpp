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
  void playSound(const char* filename);

private:
  typedef std::map<std::string, audiere::SoundEffectPtr> StreamMap;

  audiere::AudioDevicePtr m_device;
  StreamMap m_streams;
};


extern SoundEngine g_sound_engine;


#endif
