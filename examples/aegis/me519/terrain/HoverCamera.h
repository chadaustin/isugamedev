#ifndef HOVER_CAMERA_H
#define HOVER_CAMERA_H


#include "Camera.h"
#include "Terrain.h"
#include "Vector.h"


class HoverCamera : public Camera {
public:
  HoverCamera(Terrain* terrain);
  ~HoverCamera();

  const char* getName();

  void apply();
  void update(int elapsedTime);

  void onKeyDown(unsigned char key);
  void onKeyUp(unsigned char key);
  void onSpecialDown(int key);
  void onSpecialUp(int key);

private:
  Terrain* mTerrain;
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
