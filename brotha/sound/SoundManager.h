#ifndef SOUND_SOUND_MANAGER_H
#define SOUND_SOUND_MANAGER_H


#include <audiere.h>
#include "Jukebox.h"
#include "SoundEffectManager.h"


namespace sound {

   class SoundManager {
   public:
      SoundManager();
      ~SoundManager();

      Jukebox* getJukebox();
      SoundEffectManager* getSoundEffectManager();

   private:
      audiere::Context*   mContext;
      Jukebox*            mJukebox;
      SoundEffectManager* mSoundEffectManager;
   };

}


#endif
