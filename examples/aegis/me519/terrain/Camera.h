#ifndef CAMERA_H
#define CAMERA_H


class Camera {
public:
  virtual ~Camera() { }

  virtual const char* getName() = 0;

  virtual void apply() = 0;
  virtual void update(int elapsedTime) = 0;

  virtual void onKeyDown(unsigned char key) = 0;
  virtual void onKeyUp(unsigned char key) = 0;
  virtual void onSpecialDown(int key) = 0;
  virtual void onSpecialUp(int key) = 0;
};


#endif
