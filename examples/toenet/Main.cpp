#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


enum {
  BLUE = 1,  // O
  RED  = 2,  // X
};

int screen_width;
int screen_height;

int board[3][3];
int player;


const double PI = 3.14159265353898;


void drawO() {
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  for (int i = 0; i < 32; ++i) {
    int j = (i + 1) % 32;
    double x1 = cos(2 * PI * i / 16);
    double y1 = sin(2 * PI * i / 16);
    glVertex2d(x1, y1);
    double x2 = cos(2 * PI * j / 16);
    double y2 = sin(2 * PI * j / 16);
    glVertex2d(x2, y2);
  }
  glEnd();
}


void drawX() {
  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  glVertex2f(-1, -1);
  glVertex2f(+1, +1);
  glVertex2f(-1, +1);
  glVertex2f(+1, -1);
  glEnd();
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 3, 3, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // draw the board
  glColor3f(1, 1, 1);
  glBegin(GL_LINES);
  glVertex2f(1, 0);
  glVertex2f(1, 3);
  glVertex2f(2, 0);
  glVertex2f(2, 3);
  glVertex2f(0, 1);
  glVertex2f(3, 1);
  glVertex2f(0, 2);
  glVertex2f(3, 2);
  glEnd();

  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      glTranslatef(x, y, 0);
      glTranslatef(.5f, .5f, 0);
      glScalef(.4f, .4f, 0);
      if (board[x][y] == BLUE) {
	drawO();
      } if (board[x][y] == RED) {
	drawX();
      }
      glScalef(2.5f, 2.5f, 0);
      glTranslatef(-.5f, -.5f, 0);
      glTranslatef(-x, -y, 0);
    }
  }

  glutSwapBuffers();
}


void reshape(int w, int h) {
  screen_width = w;
  screen_height = h;
  glViewport(0, 0, w, h);
}


void initialize_game() {
  player = RED;
  for (int i = 0; i < 9; ++i) {
    board[i / 3][i % 3] = 0;  // empty
  }
}


void mouse(int button, int state, int x, int y) {
  if (button == 0 && state == 0) {
    // left click

    int bx = 3 * x / screen_width;
    int by = 3 * y / screen_height;
    if (board[bx][by] == 0) {
      board[bx][by] = player;
      player = (player == 1 ? 2 : 1);
      glutPostRedisplay();
    }
  } else if (button == 2 && state == 0) {
    // right click

    // reset the game
    initialize_game();
    glutPostRedisplay();
  }
}


void initialize() {
  glLineWidth(5);
}


int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitWindowSize(480, 480);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA);
  glutCreateWindow("Tic Tac Toe");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);

  initialize();
  initialize_game();

  glutMainLoop();
}
