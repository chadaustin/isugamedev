#include <GL/glut.h>
#include "RotationCamera.h"


RotationCamera::RotationCamera() {
  mAngle = 0;
  mAngleDelta = 0;
}


RotationCamera::~RotationCamera() {
}


const char*
RotationCamera::getName() {
  return "Rotation Camera";
}


void
RotationCamera::apply() {
  glLoadIdentity();
  gluLookAt(1, 1, 1,
            0, 0, 0,
            0, 0, 1);
  glRotatef(mAngle, 0, 0, 1);

  // keep the height a little exaggerated, but not too much
  glScalef(1, 1, 0.2f);
}


void
RotationCamera::update(int elapsedTime) {
  mAngle += elapsedTime * mAngleDelta / 1000;
}


void
RotationCamera::onKeyDown(unsigned char /*key*/) {
}


void
RotationCamera::onKeyUp(unsigned char /*key*/) {
}


void
RotationCamera::onSpecialDown(int key) {
  if (key == GLUT_KEY_LEFT) {
    mAngleDelta -= 10;
  } else if (key == GLUT_KEY_RIGHT) {
    mAngleDelta += 10;
  }
}


void
RotationCamera::onSpecialUp(int key) {
}
