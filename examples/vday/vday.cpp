#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


double g_width;
double g_height;

int g_last_time;


const int PARTICLE_COUNT = 5000;
const int POINT_COUNT = 5000;
const double PI = 3.1415927;


double randd() {
  return double(rand()) / RAND_MAX;
}


struct Particle {

  void create() {
    x = 0;
    y = 0;
    z = 0;
    double r = randd();
    double a = randd() * 2 * PI;
    vx = r * cos(a);
    vy = r * sin(a);
    vz = randd();
    fade = randd();
  }

  void update(double time) {
    x += 0.003 * vx * time;
    y += 0.003 * vy * time;
    z += 0.003 * vz * time;
    vz -= 0.0004 * time;
    fade -= time * 0.0002;
    if (fade < 0) {
      create();
    }
  }

  double x, y, z;
  double vx, vy, vz;
  double fade;
} g_particles[PARTICLE_COUNT];


struct Point {

  bool create() {
    x = randd() * 2 - 1;
    y = randd() * 3 - 2;

    if (y >= 0) {
      double r1 = (x - .5) * (x - .5) + (y * y);
      double r2 = (x + .5) * (x + .5) + (y * y);
      return (r1 < .5 || r2 < .5);
    } else {
      return 2 * fabs(x) < 2 + y;
    }
  }

  double x, y;
} g_points[POINT_COUNT];


void create_particles() {
  for (int i = 0; i < PARTICLE_COUNT; ++i) {
    g_particles[i].create();
  }
}

void update_particles(int ms) {
  for (int i = 0; i < PARTICLE_COUNT; ++i) {
    g_particles[i].update(ms);
  }
}

void create_points() {
  for (int i = 0; i < POINT_COUNT; ++i) {
    while (!g_points[i].create()) {
    }
  }
}


void initialize() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_POLYGON_SMOOTH);

  glEnable(GL_POINT_SMOOTH);
  glPointSize(4.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  g_last_time = glutGet(GLUT_ELAPSED_TIME);
  create_particles();
  create_points();
}


void display() {

  void particles();
  void heart();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double width  = g_width;
  double height = (g_height == 0 ? 1 : g_height);
  gluPerspective(90, width / height, 0.001, 20);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, -6, 2, 0, 0, 0, 0, 0, 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  heart();
  particles();

  glutSwapBuffers();
}


void particles() {
  glRotated(glutGet(GLUT_ELAPSED_TIME) / 50.0, 0, 0, 1);

  glBegin(GL_POINTS);
  for (int i = 0; i < PARTICLE_COUNT; ++i) {
    Particle& p = g_particles[i];
    glColor4d(1, 0, 1, p.fade);
    glVertex3d(p.x, p.y, p.z);
  }
  glEnd();
}


void heart() {
  double angle = glutGet(GLUT_ELAPSED_TIME) / 10.0;
  glRotated(angle, 0, 0, 1);
  glScaled(2, 2, 2);

  glColor3f(1, 0, 0);
  glBegin(GL_POINTS);
  for (int i = 0; i < POINT_COUNT; ++i) {
    Point& p = g_points[i];
    glVertex3d(p.x, 0, p.y + .5);
  }
  glEnd();

  glScaled(0.5, 0.5, 0.5);
  glRotated(-angle, 0, 0, 1);
}


void reshape(int w, int h) {
  g_width = w;
  g_height = h;
  glViewport(0, 0, w, h);
  glutPostRedisplay();
}


void idle() {
  int time = glutGet(GLUT_ELAPSED_TIME);
  update_particles(time - g_last_time);
  g_last_time = time;
  glutPostRedisplay();
}


int main(int argc, char** argv) {
  srand(time(0));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);

  glutCreateWindow("Happy Valentine's Day!");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);

  initialize();
  glutMainLoop();

  // VC++ sucks
  return 0;
}


#ifdef _WIN32

#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  return main(__argc, __argv);
}

#endif
