#include <GL/glut.h>
#include <math.h>
#include "HoverCamera.h"
#include "Math.h"


HoverCamera::HoverCamera(Terrain* terrain) {
  mTerrain = terrain;

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


HoverCamera::~HoverCamera() {
}


const char*
HoverCamera::getName() {
  return "Hover Camera";
}


void
HoverCamera::apply() {
  glRotatef(mPitch, 1, 0, 0);
  glRotatef(-mHeading, 0, 0, 1);
  glTranslate(-mPosition);

  glScalef(10, 10, 0.4f);

  // make all of our virtual function calls in one place, caching the
  // results
  int width = mTerrain->getWidth();
  int height = mTerrain->getHeight();
  float* heightmap = mTerrain->getHeightMap();

  // Calculate the height of the current position in the terrain and
  // offset our height by that. The terrain exists from (-5, -5) to
  // (5, 5).
  float tX = (mPosition.x + 5) / 10 * (width - 1);
  float tY = (mPosition.y + 5) / 10 * (height - 1);

  float z = 0;  // this is the base offset if we're off of the terrain
  if (tX >= 0 && tX < width - 1 && tY >= 0 && tY < height - 1) {
    // find the corners of our current position
    int tX1 = Floor(tX);   int tY1 = Floor(tY);
    int tX2 = Ceiling(tX); int tY2 = Ceiling(tY);

    float z1 = heightmap[tY1 * width + tX1];
    float z2 = heightmap[tY1 * width + tX2];
    float z3 = heightmap[tY2 * width + tX1];
    float z4 = heightmap[tY2 * width + tX2];

    // calculate the weights of the various corners
    float wX = tX - tX1;
    float wY = tY - tY1;

    // find the terrain's current offset
    float Z1 = (z1 * (1 - wX) + z2 * wX);
    float Z2 = (z3 * (1 - wX) + z4 * wX);
    z = Z1 * (1 - wY) + Z2 * wY;
  }
  glTranslatef(0, 0, -z);
}


void
HoverCamera::update(int elapsedTime) {
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
HoverCamera::onKeyDown(unsigned char key) {
  if (key == 'a') {
    mVerticalVelocity += 0.001;
  } else if (key == 'z') {
    mVerticalVelocity -= 0.001;
  } else if (key == ' ') {
    mVelocity = 0;
  }
}


void
HoverCamera::onKeyUp(unsigned char key) {
  if (key == 'a') {
    mVerticalVelocity -= 0.001;
  } else if (key == 'z') {
    mVerticalVelocity += 0.001;
  }
}


void
HoverCamera::onSpecialDown(int key) {
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
HoverCamera::onSpecialUp(int key) {
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
