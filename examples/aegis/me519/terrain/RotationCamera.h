#ifndef ROTATION_CAMERA_H
#define ROTATION_CAMERA_H


#include "Camera.h"


class RotationCamera : public Camera {
public:
  RotationCamera();
  ~RotationCamera();

  const char* getName();

  void apply();
  void update(int elapsedTime);

  void onKeyDown(unsigned char key);
  void onKeyUp(unsigned char key);
  void onSpecialDown(int key);
  void onSpecialUp(int key);

private:
  float mAngle;
  float mAngleDelta;  // degrees per second
};


#endif
