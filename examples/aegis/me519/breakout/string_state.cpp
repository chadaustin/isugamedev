#include <GL/glut.h>
#include "string_state.hpp"
#include "text.hpp"


StringState::StringState(const std::string& text)
  : m_text(text)
{
}

void
StringState::draw()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0, 1, 1, 0, -1, 1);

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1, 1, 1);
  DrawBitmapText(0.1, 0.1, GLUT_BITMAP_HELVETICA_10, m_text.c_str());
}
