#ifndef APPLICATION_H
#define APPLICATION_H


class Application {
public:
  virtual ~Application() { }
  virtual void draw() = 0;
  virtual void resize(int width, int height) = 0;
  virtual void update(int elapsedTime) = 0;

  virtual void onKeyDown(unsigned char key) = 0;
  virtual void onKeyUp(unsigned char key) = 0;
  virtual void onSpecialDown(int key) = 0;
  virtual void onSpecialUp(int key) = 0;
};


#endif
