#ifndef AMBIENT_WIND_H
#define AMBIENT_WIND_H


#include <audiere.h>


class AmbientWind {
public:
  AmbientWind();

  void update(int elapsedTime);

private:
  audiere::AudioDevicePtr mContext;
  audiere::OutputStreamPtr mSound1;
  audiere::OutputStreamPtr mSound2;
  
  int mTimeUntilUpdate;
  int mTotalTime;
};


#endif
