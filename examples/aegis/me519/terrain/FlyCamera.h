#ifndef FLY_CAMERA_H
#define FLY_CAMERA_H


#include "Camera.h"
#include "Vector.h"


class FlyCamera : public Camera {
public:
  FlyCamera();
  ~FlyCamera();

  const char* getName();

  void apply();
  void update(int elapsedTime);

  void onKeyDown(unsigned char key);
  void onKeyUp(unsigned char key);
  void onSpecialDown(int key);
  void onSpecialUp(int key);

private:
  Vector mPosition;
  float mVelocity;
  float mVerticalVelocity;
  float mHeading;
  float mPitch;
  float mPitchVelocity;
  bool mLeftPressed;
  bool mRightPressed;
  bool mUpPressed;
  bool mDownPressed;
};


#endif
