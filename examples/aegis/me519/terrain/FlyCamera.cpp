#include <GL/glut.h>
#include <math.h>
#include "FlyCamera.h"
#include "Math.h"


FlyCamera::FlyCamera() {
  mPosition.z       = 0.2f;
  mVelocity         = 0;
  mVerticalVelocity = 0;
  mHeading          = 0;
  mPitch            = 0;
  mPitchVelocity    = 0;
  mLeftPressed  = false;
  mRightPressed = false;
  mUpPressed    = false;
  mDownPressed  = false;
}


FlyCamera::~FlyCamera() {
}


const char*
FlyCamera::getName() {
  return "Fly Camera";
}


void
FlyCamera::apply() {
  glRotatef(mPitch, 1, 0, 0);
  glRotatef(-mHeading, 0, 0, 1);
  glTranslate(-mPosition);

  // keep height exaggerated a little
  glScalef(10, 10, 0.4f);
}


void
FlyCamera::update(int elapsedTime) {
  float angle = DegreesToRadians(mHeading);
  mPosition.x += sin(angle) * mVelocity;
  mPosition.y -= cos(angle) * mVelocity;
  mPosition.z += mVerticalVelocity * elapsedTime;
  mPitch += mPitchVelocity;

  if (mLeftPressed) {
    mHeading -= elapsedTime * 0.05f;
  }
  if (mRightPressed) {
    mHeading += elapsedTime * 0.05f;
  }
  if (mUpPressed) {
    mVelocity += elapsedTime * 0.0001f;
  }
  if (mDownPressed) {
    mVelocity -= elapsedTime * 0.0001f;
  }
}


void
FlyCamera::onKeyDown(unsigned char key) {
  if (key == 'a') {
    mVerticalVelocity += 0.001;
  } else if (key == 'z') {
    mVerticalVelocity -= 0.001;
  } else if (key == ' ') {
    mVelocity = 0;
  }
}


void
FlyCamera::onKeyUp(unsigned char key) {
  if (key == 'a') {
    mVerticalVelocity -= 0.001;
  } else if (key == 'z') {
    mVerticalVelocity += 0.001;
  }
}


void
FlyCamera::onSpecialDown(int key) {
  if (key == GLUT_KEY_LEFT) {
    mLeftPressed = true;
  } else if (key == GLUT_KEY_RIGHT) {
    mRightPressed = true;
  } else if (key == GLUT_KEY_UP) {
    mUpPressed = true;
  } else if (key == GLUT_KEY_DOWN) {
    mDownPressed = true;
  } else if (key == GLUT_KEY_PAGE_DOWN) {
    mPitchVelocity += 0.1;
  } else if (key == GLUT_KEY_PAGE_UP) {
    mPitchVelocity -= 0.1;
  }
}


void
FlyCamera::onSpecialUp(int key) {
  if (key == GLUT_KEY_LEFT) {
    mLeftPressed = false;
  } else if (key == GLUT_KEY_RIGHT) {
    mRightPressed = false;
  } else if (key == GLUT_KEY_UP) {
    mUpPressed = false;
  } else if (key == GLUT_KEY_DOWN) {
    mDownPressed = false;
  } else if (key == GLUT_KEY_PAGE_DOWN) {
    mPitchVelocity -= 0.1;
  } else if (key == GLUT_KEY_PAGE_UP) {
    mPitchVelocity += 0.1;
  }
}
