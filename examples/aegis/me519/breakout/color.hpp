#ifndef COLOR_HPP
#define COLOR_HPP


#include <GL/glut.h>


struct Color3d {
  Color3d(double r = 0, double g = 0, double b = 0) {
    red   = r;
    green = g;
    blue  = b;
  }

  double red, green, blue;
};


inline void glColor(const Color3d& c) {
  glColor3d(c.red, c.green, c.blue);
}


#endif
