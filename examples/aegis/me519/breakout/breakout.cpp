#include <GL/glut.h>
#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "game_state.hpp"
#include "string_state.hpp"


enum {
  COMMAND_NEW_GAME,
  COMMAND_QUIT,
  DIFFICULTY_EASY,
  DIFFICULTY_MEDIUM,
  DIFFICULTY_HARD,
};


const char* const START_MESSAGE =
  "Right-click to select a difficulty and start the game\n"
  "Difficulty: Medium";


int g_width;
int g_height;
int g_last_time;
int g_difficulty = DIFFICULTY_MEDIUM;


std::string GetStartMessage() {
  static const std::string START_MESSAGE =
    "Right-click to select a difficulty and start the game\n"
    "Difficulty: ";

  switch (g_difficulty) {
    case DIFFICULTY_EASY:   return START_MESSAGE + "Easy";
    case DIFFICULTY_MEDIUM: return START_MESSAGE + "Medium";
    case DIFFICULTY_HARD:   return START_MESSAGE + "Hard";
    default:                return START_MESSAGE + "Unknown";
  }
}


State* g_state = new StringState(GetStartMessage());


void on_display() {
  glViewport(0, 0, g_width, g_height);
  g_state->draw();
  glutSwapBuffers();
}

void on_reshape(int width, int height) {
  g_width = width;
  g_height = height;
  glutPostRedisplay();
}

void on_idle() {
  int time = glutGet(GLUT_ELAPSED_TIME);
  g_state->update(time - g_last_time);
  g_last_time = time;
  
  glutPostRedisplay();
}

void on_mouse_click(int button, int state, int x, int y) {
}

void on_mouse_move(int x, int y) {
  g_state->onMouseMove(double(x) / g_width, double(y) / g_height);
}

void on_key_down(unsigned char key, int x, int y) {
}

void on_key_up(unsigned char key, int x, int y) {
}

void on_special_key_down(int key, int x, int y) {
}

void on_special_key_up(int key, int x, int y) {
}

void main_menu(int value) {
  switch (value) {
    case COMMAND_NEW_GAME:
      delete g_state;
      switch (g_difficulty) {
	case DIFFICULTY_EASY:
	  g_state = new GameState(GameState::EASY);
	  break;
	case DIFFICULTY_MEDIUM:
	  g_state = new GameState(GameState::MEDIUM);
	  break;
	case DIFFICULTY_HARD:
	  g_state = new GameState(GameState::HARD);
	  break;
	default:
	  g_state = new StringState(GetStartMessage());
	  break;
      }
      break;
      
    case COMMAND_QUIT:
      exit(EXIT_SUCCESS);
      break;
  }

  // update time...  menus mess it up
  g_last_time = glutGet(GLUT_ELAPSED_TIME);
}

void difficulty_menu(int value) {
  g_difficulty = value;

  delete g_state;
  g_state = new StringState(GetStartMessage());

  // update time...  menus mess it up
  g_last_time = glutGet(GLUT_ELAPSED_TIME);
}

void create_menu() {
  int difficulty = glutCreateMenu(difficulty_menu);
  glutAddMenuEntry("Easy",   DIFFICULTY_EASY);
  glutAddMenuEntry("Medium", DIFFICULTY_MEDIUM);
  glutAddMenuEntry("Hard",   DIFFICULTY_HARD);

  glutCreateMenu(main_menu);
  glutAddMenuEntry("New Game", COMMAND_NEW_GAME);
  glutAddSubMenu("Difficulty", difficulty);
  glutAddMenuEntry("Quit",     COMMAND_QUIT);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
  srand(time(NULL));

  glutInit(&argc, argv);
  glutInitWindowSize(480, 480);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutCreateWindow("Breakout");

  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutIdleFunc(on_idle);

  // mouse input
  glutMouseFunc(on_mouse_click);
  glutMotionFunc(on_mouse_move);
  glutPassiveMotionFunc(on_mouse_move);

  // keyboard input
  glutKeyboardFunc(on_key_down);
  glutKeyboardUpFunc(on_key_up);
  glutSpecialFunc(on_special_key_down);
  glutSpecialUpFunc(on_special_key_up);

  glutSetCursor(GLUT_CURSOR_NONE);

  create_menu();
  glutMainLoop();

  // VC++ sucks again
  // according to the C++ standard, you're allowed to simply leave main, which
  // implicitly calls exit(0)
  return 0;
}


#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  return main(__argc, __argv);
}
#endif
