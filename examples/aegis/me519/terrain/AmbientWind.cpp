#include <memory>
#include <stdexcept>
#include <math.h>
#include "AmbientWind.h"


// Don't always update the volume, since that is slow...
static const int UPDATE_GRANULARITY = 500;   // milliseconds


AmbientWind::AmbientWind() {
  std::auto_ptr<audiere::Context> context(audiere::CreateContext(0));
  if (!context.get()) {
    throw std::runtime_error("Error creating Audiere context");
  }

  std::auto_ptr<audiere::Stream> sound1(
    context->openStream("Howling Wind.ogg"));
  if (!sound1.get()) {
    throw std::runtime_error(
      "Error loading sound effect: Howling Wind.ogg");
  }

  std::auto_ptr<audiere::Stream> sound2(
    context->openStream("Moaning Wind.ogg"));
  if (!sound2.get()) {
    throw std::runtime_error(
      "Error loading sound effect: Moaning Wind.ogg");
  }

  mContext = context.release();
  mSound1  = sound1.release();
  mSound2  = sound2.release();

  mSound1->setRepeat(true);
  mSound1->play();
  
  mSound2->setRepeat(true);
  mSound2->play();
  
  mTimeUntilUpdate = 0;
  mTotalTime = 0;
}


AmbientWind::~AmbientWind() {
  delete mSound1;
  delete mSound2;
  delete mContext;
}


void
AmbientWind::update(int elapsedTime) {
   mTimeUntilUpdate -= elapsedTime;
   mTotalTime += elapsedTime;

   if (mTimeUntilUpdate <= 0) {
      float time = mTotalTime / float(10000);
      double v1 = (sin(time) + 1) / 2;
      double v2 = (-sin(time) + 1) / 2;
      
      mSound1->setVolume(int(v1 * 255));
      mSound2->setVolume(int(v2 * 255));
      
      mTimeUntilUpdate = UPDATE_GRANULARITY;
   }
}
