#ifndef SOUND_SOUND_EFFECT_MANAGER_H
#define SOUND_SOUND_EFFECT_MANAGER_H


#include <string>
#include <audiere.h>


namespace sound {

   class SoundEffectManager {
   public:
      SoundEffectManager(audiere::Context* context);
      ~SoundEffectManager();

      void playSound(const std::string& sound);

   private:
      enum { MAX_SOUNDS = 8 };
    
      audiere::Context* mContext;
      audiere::Stream* mStreams[MAX_SOUNDS];
      int mNextStream;
   };

}


#endif
