#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include "MyTerrain.h"
#include "ImageTerrain.h"
#include "PlasmaTerrain.h"
#include "TerrainApplication.h"


const char* TITLE = "Terrain Demo";


Application* gApplication = 0;
int gLastTime;
int gLastFPSUpdate;
int gDrawCount;


void display() {
  if (gApplication) {
    gApplication->draw();
    glutSwapBuffers();
    ++gDrawCount;
  }
}


void reshape(int w, int h) {
  if (gApplication) {
    glViewport(0, 0, w, h);
    gApplication->resize(w, h);
  }
}


void idle() {
  if (gApplication) {
    int time = glutGet(GLUT_ELAPSED_TIME);

    // guard against wraparound
    if (time > gLastTime) {
      gApplication->update(time - gLastTime);
    }

    gLastTime = time;

    glutPostRedisplay();

    if (time > gLastFPSUpdate + 1000) {

      char title[200];
      sprintf(title, "%s - FPS %d", TITLE, gDrawCount);
      glutSetWindowTitle(title);

      gLastFPSUpdate = time;
      gDrawCount = 0;
    }
  }
}


void keyboard(unsigned char key, int /*x*/, int /*y*/) {
  if (gApplication) {
    gApplication->onKeyDown(key);
  }
}

void keyboardUp(unsigned char key, int /*x*/, int /*y*/) {
  if (gApplication) {
    gApplication->onKeyUp(key);
  }
}

void special(int key, int /*x*/, int /*y*/) {
  if (gApplication) {
    gApplication->onSpecialDown(key);
  }
}

void specialUp(int key, int /*x*/, int /*y*/) {
  if (gApplication) {
    gApplication->onSpecialUp(key);
  }
}


void cleanup() {
  delete gApplication;
}


int main(int argc, char** argv) {
  try {
    srand(time(0));

    if (argc != 3) {
      puts("usage: terrain <mode> argument");
      puts("where mode is one of:");
      puts("  my <power>");
      puts("  plasma <power>");
      puts("  image <filename");
      return 0;
    }

    glutInit(&argc, argv);
    const char* mode = argv[1];
    const char* parameter = argv[2];

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    glutCreateWindow(TITLE);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);

    glutIgnoreKeyRepeat(1);
  
    Terrain* terrain;
    if (strcmp(mode, "my") == 0) {
      terrain = new MyTerrain(atoi(parameter));
    } else if (strcmp(mode, "plasma") == 0) {
      terrain = new PlasmaTerrain(atoi(parameter));
    } else if (strcmp(mode, "image") == 0) {
      terrain = new ImageTerrain(parameter);
    } else {
      puts("invalid mode");
      return 0;
    }

    gApplication = new TerrainApplication(terrain);

    gLastTime = glutGet(GLUT_ELAPSED_TIME);
    gLastFPSUpdate = gLastTime;

    atexit(cleanup);
    glutMainLoop();
  }
  catch (const std::exception& e) {
    printf("Uncaught exception: %s\n", e.what());
  }
}


#ifdef WIN32

#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  return main(__argc, __argv);
}

#endif
