#include <GL/gl.h>
#include "Window.h"


namespace phui {

  Window::Window() {
  }

  Window::~Window() {
  }

  void Window::draw() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_STRIP);
    // draw a rectangle around the size or something
    glEnd();
  }

}
