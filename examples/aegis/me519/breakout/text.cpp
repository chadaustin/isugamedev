#include <GL/glut.h>
#include "text.hpp"


void DrawBitmapText(double x, double y, void* font, const char* text) {
  glRasterPos2d(x, y);
  while (*text) {
    if (*text == '\n') {
      y += 0.1;
      glRasterPos2d(x, y);
    } else {
      glutBitmapCharacter(font, *text);
    }
    ++text;
  }
}


void DrawStrokeText(void* font, const char* text) {
  while (*text) {
    glutStrokeCharacter(font, *text++);
  }
}
