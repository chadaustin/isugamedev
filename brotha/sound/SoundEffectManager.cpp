#include "SoundEffectManager.h"


namespace sound {

   SoundEffectManager::SoundEffectManager(audiere::Context* context) {
      mContext = context;
      mNextStream = 0;
      for (int i = 0; i < MAX_SOUNDS; ++i) {
         mStreams[i] = 0;
      }
   }


   SoundEffectManager::~SoundEffectManager() {
      for (int i = 0; i < MAX_SOUNDS; ++i) {
         delete mStreams[i];
      }
   }


   void
   SoundEffectManager::playSound(const std::string& sound) {

      delete mStreams[mNextStream];
      audiere::Stream* stream = mContext->openStream(sound.c_str());
      if (stream) {
         stream->play();
      }
      mStreams[mNextStream] = stream;

      mNextStream = (mNextStream + 1) % MAX_SOUNDS;
   }

}
