#include <stdio.h>
#include "NullAudioSystem.h"


NullAudioSystem::NullAudioSystem()
{
}


NullAudioSystem::~NullAudioSystem()
{
}


bool
NullAudioSystem::initialize(const char* /*device*/, const char* /*parameters*/)
{
   return true;
}


bool
NullAudioSystem::play(const char* filename)
{
   // check to see if the file exists
   FILE* file = fopen(filename, "rb");
   if (file) {
      fclose(file);
      return true;
   } else {
      return false;
   }
}


bool
NullAudioSystem::playMusic(const char* filename)
{
   // check to see if the file exists
   FILE* file = fopen(filename, "rb");
   if (file) {
      fclose(file);
      return true;
   } else {
      return false;
   }
}
