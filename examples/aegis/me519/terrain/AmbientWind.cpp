#include <memory>
#include <stdexcept>
#include <math.h>
#include "AmbientWind.h"


// Don't always update the volume, since that is slow...
static const int UPDATE_GRANULARITY = 500;   // milliseconds


AmbientWind::AmbientWind() {
  mContext = audiere::OpenDevice();
  if (!mContext) {
    throw std::runtime_error("Error creating Audiere context");
  }

  mSound1 = audiere::OpenSound(mContext.get(), "Howling Wind.ogg");
  if (!mSound1) {
    throw std::runtime_error(
      "Error loading sound effect: Howling Wind.ogg");
  }

  mSound2 = audiere::OpenSound(mContext.get(), "Moaning Wind.ogg");
  if (!mSound2) {
    throw std::runtime_error(
      "Error loading sound effect: Moaning Wind.ogg");
  }

  mSound1->setRepeat(true);
  mSound1->play();
  
  mSound2->setRepeat(true);
  mSound2->play();
  
  mTimeUntilUpdate = 0;
  mTotalTime = 0;
}


void
AmbientWind::update(int elapsedTime) {
   mTimeUntilUpdate -= elapsedTime;
   mTotalTime += elapsedTime;

   if (mTimeUntilUpdate <= 0) {
      float time = mTotalTime / float(10000);
      float v1 = ( sinf(time) + 1) / 2;
      float v2 = (-sinf(time) + 1) / 2;
      
      mSound1->setVolume(v1);
      mSound2->setVolume(v2);
      
      mTimeUntilUpdate = UPDATE_GRANULARITY;
   }
}
