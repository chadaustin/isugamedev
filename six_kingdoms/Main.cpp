#include <GL/glut.h>


void display() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0, 1, 1, 0, -1, 1);

  glClear(GL_COLOR_BUFFER_BIT);
 
  glColor3f(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  glVertex2f(.5f, 0);
  glVertex2f(0,   1);
  glVertex2f(1,   1);
  glVertex2f(.5f, 0);
  glEnd();

  glutSwapBuffers();
}


void reshape(int width, int height) {
  glViewport(0, 0, width, height);
}


void initialize_gl() {
  glClearColor(0, 0, 0, 0);
}


int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutCreateWindow("Six Kingdoms");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  initialize_gl();
  glutMainLoop();
}
