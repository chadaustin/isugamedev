#include <algorithm>
#include <functional>
#include <list>
#include <stdlib.h>
#include <GL/glut.h>
using namespace std;


struct Point {
  Point(int x_ = 0, int y_ = 0) {
    x = x_;
    y = y_;
  }

  int x;
  int y;
};


struct Color {
  float red, green, blue, alpha;
};

static const Color white   = { 1, 1, 1 };
static const Color black   = { 0, 0, 0 };
static const Color red     = { 1, 0, 0 };
static const Color green   = { 0, 1, 0 };
static const Color blue    = { 0, 0, 1 };
static const Color cyan    = { 0, 1, 1 };
static const Color magenta = { 1, 0, 1 };
static const Color yellow  = { 1, 1, 0 };


inline void glColor(const Color& c) {
  glColor4f(c.red, c.green, c.blue, c.alpha);
}
inline void glVertex(const Point& p) {
  glVertex2i(p.x, p.y);
}


struct Command {
  virtual ~Command() {}
  void destroy() { delete this; }
  virtual void draw() = 0;
};

struct PointCommand : Command {
  PointCommand(Point p_, Color c_, int size_) {
    p = p_;
    c = c_;
    size = size_;
  }

  void draw() {
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor(c);
    glVertex(p);
    glEnd();
  }

private:
  Point p;
  Color c;
  int size;
};

struct LineCommand : Command {
  LineCommand(Point p1_, Point p2_, Color c_, int width_) {
    p1 = p1_;
    p2 = p2_;
    c = c_;
    width = width_;
  }

  void draw() {
    glLineWidth(width);
    glColor(c);
    glBegin(GL_LINES);
    glVertex(p1);
    glVertex(p2);
    glEnd();
  }

private:
  Point p1;
  Point p2;
  Color c;
  int width;
};

struct RectangleCommand : Command {
  RectangleCommand(Point p1_, Point p2_, Color c_, int width_) {
    p1    = p1_;
    p2    = p2_;
    c     = c_;
    width = width_;
  }

  void draw() {
    glLineWidth(width);
    glColor(c);
    glBegin(GL_LINE_STRIP);
    glVertex(p1);
    glVertex2i(p2.x, p1.y);
    glVertex(p2);
    glVertex2i(p1.x, p2.y);
    glVertex(p1);
    glEnd();
  }

private:
  Point p1;
  Point p2;
  Color c;
  int width;
};

struct FilledRectangleCommand : Command {
  FilledRectangleCommand(Point p1_, Point p2_, Color c_) {
    p1 = p1_;
    p2 = p2_;
    c  = c_;
  }

  void draw() {
    glColor(c);
    glBegin(GL_QUADS);
    glVertex(p1);
    glVertex2i(p2.x, p1.y);
    glVertex(p2);
    glVertex2i(p1.x, p2.y);
    glEnd();
  }

private:
  Point p1;
  Point p2;
  Color c;
};


struct CommandList {

  void add(Command* c) {
    for_each(redos.begin(), redos.end(), mem_fun(&Command::destroy));
    redos.clear();

    commands.push_back(c);
    glutPostRedisplay();
  }

  void undo() {
    if (commands.size()) {
      redos.push_back(commands.back());
      commands.pop_back();
      glutPostRedisplay();
    }
  }

  void redo() {
    if (redos.size()) {
      commands.push_back(redos.back());
      redos.pop_back();
      glutPostRedisplay();
    }
  }

  void clear() {
    for_each(commands.begin(), commands.end(), mem_fun(&Command::destroy));
    commands.clear();

    for_each(redos.begin(), redos.end(), mem_fun(&Command::destroy));
    redos.clear();

    glutPostRedisplay();
  }

  void draw() {
    for_each(commands.begin(), commands.end(), mem_fun(&Command::draw));
  }

private:
  list<Command*> commands;
  list<Command*> redos;
};


// since all tools use the same color...
Color g_color = white;
float g_alpha = 1;
int g_line_width = 1;
int g_point_size = 1;
CommandList g_commands;


Color CreateColor() {
  Color c = g_color;
  c.alpha = g_alpha;
  return c;
}


struct Tool {
  virtual void onMouseDown(Point p) { }
  virtual void onMouseMove(Point p) { }

  static void pushCommand(Command* c) {
    g_commands.add(c);
  }

  static void popCommand() {
    g_commands.undo();
  }
};

struct PointToolClass : Tool {
  void onMouseDown(Point p) {
    pushCommand(new PointCommand(p, CreateColor(), g_point_size));
  }
} PointTool;

struct ScribbleToolClass : Tool {
  void onMouseDown(Point p) {
    m_last_point = p;
  }

  void onMouseMove(Point p) {
    pushCommand(new LineCommand(m_last_point, p, CreateColor(), g_line_width));
    m_last_point = p;
  }

private:
  Point m_last_point;
} ScribbleTool;

struct LineToolClass : Tool {
  void onMouseDown(Point p) {
    m_start = p;
    pushCommand(getCommand(p));
  }
  
  void onMouseMove(Point p) {
    popCommand();
    pushCommand(getCommand(p));
  }

private:
  Command* getCommand(Point p) {
    return new LineCommand(m_start, p, CreateColor(), g_line_width);
  }

  Point m_start;
} LineTool;

struct RectangleToolClass : Tool {
  RectangleToolClass() {
    m_filled = false;
  }

  void onMouseDown(Point p) {
    m_start = p;
    pushCommand(getCommand(p));
  }

  void onMouseMove(Point p) {
    popCommand();
    pushCommand(getCommand(p));
  }

  void setFill(bool filled) {
    m_filled = filled;
  }

private:
  Command* getCommand(Point p) {
    if (m_filled) {
      return new FilledRectangleCommand(m_start, p, CreateColor());
    } else {
      return new RectangleCommand(m_start, p, CreateColor(), g_line_width);
    }
  }

private:
  Point m_start;
  bool m_filled;
} RectangleTool;


int g_width;
int g_height;
Tool* g_tool = &PointTool;

void display() {
  glViewport(0, 0, g_width, g_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, g_width, g_height, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT);
  g_commands.draw();
  glutSwapBuffers();
}

void reshape(int x, int y) {
  g_width  = x;
  g_height = y;
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    g_tool->onMouseDown(Point(x, y));
  }
}

void motion(int x, int y) {
  g_tool->onMouseMove(Point(x, y));
}


// menu commands
enum {
  TOOL_POINT,
  TOOL_SCRIBBLE,
  TOOL_LINE,
  TOOL_RECTANGLE,
  COLOR_WHITE,
  COLOR_BLACK,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_CYAN,
  COLOR_MAGENTA,
  COLOR_YELLOW,
  TRANSPARENCY_0,
  TRANSPARENCY_10,
  TRANSPARENCY_20,
  TRANSPARENCY_30,
  TRANSPARENCY_40,
  TRANSPARENCY_50,
  TRANSPARENCY_60,
  TRANSPARENCY_70,
  TRANSPARENCY_80,
  TRANSPARENCY_90,
  TRANSPARENCY_100,
  POINT_SIZE_1,
  POINT_SIZE_2,
  POINT_SIZE_4,
  POINT_SIZE_8,
  LINE_WIDTH_1,
  LINE_WIDTH_2,
  LINE_WIDTH_4,
  LINE_WIDTH_8,
  FILL_ON,
  FILL_OFF,
  COMMAND_REDO,
  COMMAND_UNDO,
  COMMAND_CLEAR,
  COMMAND_QUIT,
};

void main_menu(int value) {
  switch (value) {

  case COMMAND_UNDO:  g_commands.undo(); break;
  case COMMAND_REDO:  g_commands.redo(); break;
  case COMMAND_CLEAR: g_commands.clear(); break;
  case COMMAND_QUIT:  exit(EXIT_SUCCESS);

  }
}

void tool_menu(int value) {
  switch (value) {
  case TOOL_POINT:     g_tool = &PointTool;     break;
  case TOOL_SCRIBBLE:  g_tool = &ScribbleTool;  break;
  case TOOL_LINE:      g_tool = &LineTool;      break;
  case TOOL_RECTANGLE: g_tool = &RectangleTool; break;
  }
}

void color_menu(int value) {
  switch (value) {
  case COLOR_WHITE:   g_color = white;   break;
  case COLOR_BLACK:   g_color = black;   break;
  case COLOR_RED:     g_color = red;     break;
  case COLOR_GREEN:   g_color = green;   break;
  case COLOR_BLUE:    g_color = blue;    break;
  case COLOR_CYAN:    g_color = cyan;    break;
  case COLOR_MAGENTA: g_color = magenta; break;
  case COLOR_YELLOW:  g_color = yellow;  break;
  }
}

void transparency_menu(int value) {
  switch (value) {
  case TRANSPARENCY_0:   g_alpha = 0.0f; break;
  case TRANSPARENCY_10:  g_alpha = 0.1f; break;
  case TRANSPARENCY_20:  g_alpha = 0.2f; break;
  case TRANSPARENCY_30:  g_alpha = 0.3f; break;
  case TRANSPARENCY_40:  g_alpha = 0.4f; break;
  case TRANSPARENCY_50:  g_alpha = 0.5f; break;
  case TRANSPARENCY_60:  g_alpha = 0.6f; break;
  case TRANSPARENCY_70:  g_alpha = 0.7f; break;
  case TRANSPARENCY_80:  g_alpha = 0.8f; break;
  case TRANSPARENCY_90:  g_alpha = 0.9f; break;
  case TRANSPARENCY_100: g_alpha = 1.0f; break;
  }
}

void point_size_menu(int value) {
  switch (value) {
  case POINT_SIZE_1: g_point_size = 1; break;
  case POINT_SIZE_2: g_point_size = 2; break;
  case POINT_SIZE_4: g_point_size = 4; break;
  case POINT_SIZE_8: g_point_size = 8; break;
  }
}

void line_width_menu(int value) {
  switch (value) {
  case LINE_WIDTH_1: g_line_width = 1; break;
  case LINE_WIDTH_2: g_line_width = 2; break;
  case LINE_WIDTH_4: g_line_width = 4; break;
  case LINE_WIDTH_8: g_line_width = 8; break;
  }
}

void fill_menu(int value) {
  RectangleTool.setFill(value == FILL_ON);
}

void create_menu() {
  int tool = glutCreateMenu(tool_menu);
  glutAddMenuEntry("Point",     TOOL_POINT);
  glutAddMenuEntry("Scribble",  TOOL_SCRIBBLE);
  glutAddMenuEntry("Line",      TOOL_LINE);
  glutAddMenuEntry("Rectangle", TOOL_RECTANGLE);

  int color = glutCreateMenu(color_menu);
  glutAddMenuEntry("White",   COLOR_WHITE);
  glutAddMenuEntry("Black",   COLOR_BLACK);
  glutAddMenuEntry("Red",     COLOR_RED);
  glutAddMenuEntry("Green",   COLOR_GREEN);
  glutAddMenuEntry("Blue",    COLOR_BLUE);
  glutAddMenuEntry("Cyan",    COLOR_CYAN);
  glutAddMenuEntry("Magenta", COLOR_MAGENTA);
  glutAddMenuEntry("Yellow",  COLOR_YELLOW);

  int transparency = glutCreateMenu(transparency_menu);
  glutAddMenuEntry("0%",   TRANSPARENCY_0);
  glutAddMenuEntry("10%",  TRANSPARENCY_10);
  glutAddMenuEntry("20%",  TRANSPARENCY_20);
  glutAddMenuEntry("30%",  TRANSPARENCY_30);
  glutAddMenuEntry("40%",  TRANSPARENCY_40);
  glutAddMenuEntry("50%",  TRANSPARENCY_50);
  glutAddMenuEntry("60%",  TRANSPARENCY_60);
  glutAddMenuEntry("70%",  TRANSPARENCY_70);
  glutAddMenuEntry("80%",  TRANSPARENCY_80);
  glutAddMenuEntry("90%",  TRANSPARENCY_90);
  glutAddMenuEntry("100%", TRANSPARENCY_100);

  int point_size = glutCreateMenu(point_size_menu);
  glutAddMenuEntry("1", POINT_SIZE_1);
  glutAddMenuEntry("2", POINT_SIZE_2);
  glutAddMenuEntry("4", POINT_SIZE_4);
  glutAddMenuEntry("8", POINT_SIZE_8);

  int line_width = glutCreateMenu(line_width_menu);
  glutAddMenuEntry("1", LINE_WIDTH_1);
  glutAddMenuEntry("2", LINE_WIDTH_2);
  glutAddMenuEntry("4", LINE_WIDTH_4);
  glutAddMenuEntry("8", LINE_WIDTH_8);

  int fill = glutCreateMenu(fill_menu);
  glutAddMenuEntry("On",  FILL_ON);
  glutAddMenuEntry("Off", FILL_OFF);

  glutCreateMenu(main_menu);
  glutAddMenuEntry("Undo", COMMAND_UNDO);
  glutAddMenuEntry("Redo", COMMAND_REDO);
  glutAddSubMenu("Tool",         tool);
  glutAddSubMenu("Color",        color);
  glutAddSubMenu("Transparency", transparency);
  glutAddSubMenu("Point Size",   point_size);
  glutAddSubMenu("Line Width",   line_width);
  glutAddSubMenu("Fill",         fill);
  glutAddMenuEntry("Clear", COMMAND_CLEAR);
  glutAddMenuEntry("Quit",  COMMAND_QUIT);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initialize() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_POINT_SMOOTH);
}

int main(int argc, char** argv) {

  // initialize GLUT
  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  // create primary window
  glutCreateWindow("Paint");

  // callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  create_menu();
  initialize();
  glutMainLoop();
}
