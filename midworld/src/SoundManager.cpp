#include <stdexcept>
#include "SoundManager.h"

namespace mw
{
   SoundManager::SoundManager()
   {
      mContext = audiere::CreateContext(0);
      if (!mContext)
      {
         throw std::runtime_error("Error creating Audiere context");
      }

      mJukebox            = new Jukebox(mContext);
      mSoundEffectManager = new SoundEffectManager(mContext);
   }

   SoundManager::~SoundManager()
   {
      delete mJukebox;
      delete mSoundEffectManager;
      delete mContext;
   }

   Jukebox*
   SoundManager::getJukebox()
   {
      return mJukebox;
   }

   SoundEffectManager*
   SoundManager::getSoundEffectManager()
   {
      return mSoundEffectManager;
   }
}
