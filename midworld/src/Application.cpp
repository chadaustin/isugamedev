#include <SDL/SDL_opengl.h>
#include "Application.h"


namespace mw {

  Application::Application()
  {
    mWidth  = 0;
    mHeight = 0;
  }

  Application::~Application()
  {
  }

  void
  Application::update(u64 elapsedTime)
  {
  }

  void
  Application::draw()
  {
    // set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    float aspect_ratio = (mHeight == 0 ? 1 : float(mWidth) / mHeight);
    glOrtho(0, mWidth, mHeight, 0, -1, 1);
//    gluPerspective(45, aspect_ratio, 0.001f, 100);

    // set up view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(0, 0);
    glVertex2f(mWidth, mHeight);
    glEnd();
  }

  void
  Application::resize(int width, int height)
  {
    mWidth  = width;
    mHeight = height;
  }

  void
  Application::onKeyPress(SDLKey sym, bool down)
  {
  }

  void
  Application::onMousePress(Uint8 button, bool down, int x, int y)
  {
  }

  void
  Application::onMouseMove(int x, int y)
  {
  }

}
