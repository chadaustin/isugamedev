#ifndef AMBIENT_WIND_H
#define AMBIENT_WIND_H


#include <audiere.h>


class AmbientWind {
public:
  AmbientWind();
  ~AmbientWind();

  void update(int elapsedTime);

private:
  audiere::Context* mContext;
  audiere::Stream* mSound1;
  audiere::Stream* mSound2;
  
  int mTimeUntilUpdate;
  int mTotalTime;
};


#endif
