#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
using namespace std;


const int width = 1024;
int terrain[width][width];
int old_terrain[width][width];


void display() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(45, -1, 0, 0);
  glTranslatef(0, width, width / 2);
  long ms = 1000 * clock() / CLOCKS_PER_SEC;
  glRotatef(ms / -100.0f, 0, 0, 1);
  glTranslatef(-width / 2, -width / 2, -width * 2);

  glBegin(GL_QUADS);
  const int d = 8;
  for (int i = 0; i < width - d; i += d) {
    for (int j = 0; j < width - d; j += d) {
      float h1 = (terrain[i + 0][j + 0] + 512);
      float h2 = (terrain[i + d][j + 0] + 512);
      float h3 = (terrain[i + d][j + d] + 512);
      float h4 = (terrain[i + 0][j + d] + 512);
      float h = (h1 + h2 + h3 + h4) / (4 * width);

      glColor3f(0.0f, h, 0.0f);
      glVertex3f(i,     j,     h1);
      glVertex3f(i + d, j,     h2);
      glVertex3f(i + d, j + d, h3);
      glVertex3f(i,     j + d, h4);

    }
  }
  glEnd();

  glutSwapBuffers();
}


void reshape(int w, int h) {
  if (h == 0) {
    h = 1;
  }

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45, GLdouble(w) / h, 0.1f, 10000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void idle() {
  glutPostRedisplay();
}

int Rand1(int base, int delta) {
  return base + (rand() % delta) - delta / 2;
}

void initialize() {
  int row_offset = 0;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < width; ++j) {
      terrain[i][j] = 0;
    }
  }

  for (int square_size = width; square_size > 1; square_size /= 2) {
    int random_range = square_size;
    for (int x1 = row_offset; x1 < width; x1 += square_size) {
      for (int y1 = row_offset; y1 < width; y1 += square_size) {

	// Get the four corner points.
	int x2 = (x1 + square_size) % width;
	int y2 = (y1 + square_size) % width;

	int i1 = terrain[x1][y1];
	int i2 = terrain[x2][y1];
	int i3 = terrain[x1][y2];
	int i4 = terrain[x2][y2];

	// Obtain new points by averaging the corner points.
	int p1 = ((i1 * 9) + (i2 * 3) + (i3 * 3) + (i4)) / 16;
	int p2 = ((i1 * 3) + (i2 * 9) + (i3) + (i4 * 3)) / 16;
	int p3 = ((i1 * 3) + (i2) + (i3 * 9) + (i4 * 3)) / 16;
	int p4 = ((i1) + (i2 * 3) + (i3 * 3) + (i4 * 9)) / 16;

	// Add a random offset to each new point.
	p1 = Rand1(p1, random_range);
	p2 = Rand1(p2, random_range);
	p3 = Rand1(p3, random_range);
	p4 = Rand1(p4, random_range);
    
	// Write out the generated points.
	int x3 = (x1 + square_size/4) % width;
	int y3 = (y1 + square_size/4) % width;
	x2 = (x3 + square_size/2) % width;
	y2 = (y3 + square_size/2) % width;
    
	terrain[x3][y3] = p1;
	terrain[x2][y3] = p2;
	terrain[x3][y2] = p3;
	terrain[x2][y2] = p4;
      }
    }
    row_offset = square_size / 4;
  }

  // make the terrain tileable
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < width; ++j) {
      old_terrain[i][j] = terrain[i][j];
    }
  }
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < width; ++j) {
      int ni = (i + width / 2) % width;
      int nj = (j + width / 2) % width;
      terrain[i][j] = (old_terrain[i][j] + old_terrain[ni][nj]) / 2;
    }
  }


  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_COLOR_MATERIAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main(int argc, char** argv) {

  srand(time(NULL));

  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA);
  glutCreateWindow("Battlements Terrain Test");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);

  initialize();

  glutMainLoop();
}
