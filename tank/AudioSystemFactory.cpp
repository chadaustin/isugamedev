#include "AudioSystemFactory.h"

#ifdef USE_AUDIERE
  #include "AudiereAudioSystem.h"
  typedef AudiereAudioSystem AudioSystem;
#else
  #include "NullAudioSystem.h"
  typedef NullAudioSystem AudioSystem;
#endif


IAudioSystem* CreateAudioSystem()
{
   IAudioSystem* as = new AudioSystem();
   if (!as->initialize("", "")) {
      delete as;
      return 0;
   }

   return as;
}
