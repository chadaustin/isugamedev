#include "AudioSystemFactory.h"

#ifdef USE_AUDIERE
  #include "AudiereAudioSystem.h"
  typedef AudiereAudioSystem AudioSystem;
#elif USE_AJ
  #include "AJaudioSystem.h"
  typedef AJaudioSystem AudioSystem;
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
