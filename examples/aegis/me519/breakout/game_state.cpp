#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_state.hpp"
#include "sound.hpp"
#include "text.hpp"


static const char* NEW_GAME  = "Media/chimes.wav";
static const char* DIE       = "Media/EE_REV.wav";
static const char* LOSE_GAME = "Media/tada.wav";
static const char* PLINK     = "Media/Utopia Exclamation.WAV";
static const char* PLONK     = "Media/Utopia Question.WAV";
static const char* PLUNK     = "Media/Utopia Error.WAV";


inline double randd() {
  return double(rand()) / RAND_MAX;
}

static const double PI = asin(1) * 2;


GameState::GameState(difficulty d) {
  m_difficulty = d;
  m_level = 0;
  m_balls = 3;
  m_blocks_destroyed = 0;

  m_paddle = 0;

  resetBall();
  buildLevel();
  initializeGL();

  g_sound_engine.playSound(NEW_GAME);
}


void
GameState::draw() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-.1, 1.1, 1.2, -.1, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT);

  if (m_balls <= 0) {
    drawGameOver();
    return;
  }

  glColor3f(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  glVertex2d(0, 0);
  glVertex2d(1, 0);
  glVertex2d(1, 1);
  glVertex2d(0, 1);
  glVertex2d(0, 0);
  glEnd();

  // draw the paddle
  glBegin(GL_QUADS);
  glVertex2d(m_paddle - .1, .95);
  glVertex2d(m_paddle + .1, .95);
  glVertex2d(m_paddle + .1, .98);
  glVertex2d(m_paddle - .1, .98);
  glEnd();

  // draw the ball
  glBegin(GL_POINTS);
  glVertex2d(m_ball.position.x, m_ball.position.y);
  glEnd();

  glBegin(GL_QUADS);

  // draw the blocks
  Block::List::iterator i = m_blocks.begin();
  for (; i != m_blocks.end(); ++i) {
    glColor(i->color);
    const Point2d& ul = i->location.upper_left;
    const Point2d& lr = i->location.lower_right;
    glVertex2d(ul.x, ul.y);
    glVertex2d(lr.x, ul.y);
    glVertex2d(lr.x, lr.y);
    glVertex2d(ul.x, lr.y);
  }

  glEnd();

  drawScore();
}


void
GameState::update(int milliseconds) {

  if (m_balls <= 0) {
    return;
  }

  // update ball position
  m_ball.position += milliseconds * m_ball.velocity;

  // have we lost?
  if (m_ball.position.y >= 1) {
    resetBall();
    --m_balls;
    if (m_balls == 0) {
      g_sound_engine.playSound(LOSE_GAME);
    } else {
      g_sound_engine.playSound(DIE);
    }
    return;
  }

  detectCollisions();
}


void
GameState::onMouseMove(double x, double /*y*/) {
  m_paddle = x;
}


void
GameState::resetBall() {
  m_ball.position = Point2d(.5, .5);

  double r = getVelocityMagnitude();
  double a = (0.75 - randd() / 2) * PI;
  m_ball.velocity = Vector2d(r * cos(a), r * -sin(a));
}


void
GameState::drawScore() {
  glColor3f(1, 1, 1);
  char str[160];
  sprintf(str, "Level: %d    Balls: %d   Blocks: %d",
	  m_level, m_balls, m_blocks_destroyed);
  DrawBitmapText(0.1, 1.1, GLUT_BITMAP_HELVETICA_10, str);
}


void
GameState::drawGameOver() {
  glColor3f(1, 1, 1);
  const char* str =
    "Game Over!\n"
    "Right-click for new game";
  DrawBitmapText(0.1, 0.1, GLUT_BITMAP_HELVETICA_10, str);
}


double
GameState::getVelocityMagnitude() {
  // select a time multiplier based on the difficulty
  double scalar = 0;
  switch (m_difficulty) {
    case EASY:   scalar = .5;  break;
    case MEDIUM: scalar = 1;   break;
    case HARD:   scalar = 1.5; break;
  }
  return 0.0005 * scalar;
}


void
GameState::initializeGL() {
  glClearColor(0, 0, 0, 0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_POINT_SMOOTH);
  glPointSize(8);

  glLineWidth(2);
}


void
GameState::buildLevel() {
  m_blocks.clear();
  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 5; ++y) {
      Block bl;
      int x1 = x + 1;
      int y1 = y + 1;
      bl.location = Rectangle(
	x  / 10.0, y  / 50.0 + .05,
	x1 / 10.0, y1 / 50.0 + .05);
      double r = (randd() + 1) / 2;
      double g = (randd() + 1) / 2;
      double b = (randd() + 1) / 2;
      bl.color = Color3d(r, g, b);
      m_blocks.push_back(bl);
    }
  }
}


void
GameState::nextLevel() {
  resetBall();

  ++m_level;

  buildLevel();
}


void
GameState::detectCollisions() {

  // walls
  if (m_ball.position.x < 0 || m_ball.position.x > 1) {
    m_ball.velocity.x = -m_ball.velocity.x;
    g_sound_engine.playSound(PLINK);
    return;
  }

  // ceiling
  if (m_ball.position.y < 0) {
    m_ball.velocity.y = -m_ball.velocity.y;
    g_sound_engine.playSound(PLINK);
    return;
  }

  // paddle
  Rectangle paddle(m_paddle - 0.1, 0.95, m_paddle + 0.1, 0.98);
  if (detectCollision(paddle, true)) {
    g_sound_engine.playSound(PLUNK);
    return;
  }

  Block::List::iterator i = m_blocks.begin();
  for (; i != m_blocks.end(); ++i) {
    if (detectCollision(i->location, false)) {

      g_sound_engine.playSound(PLONK);

      m_blocks.erase(i);
      ++m_blocks_destroyed;

      // have we completed the level?
      if (m_blocks.empty()) {
	nextLevel();
      }
      
      return;
    }
  }
}


inline bool is_between(double x, double low, double high) {
  return x >= low && x <= high;
}

bool
GameState::detectCollision(const Rectangle& r, bool modify_angle) {
  const Point2d& p = m_ball.position;

  if (is_between(p.x, r.upper_left.x, r.lower_right.x) &&
      is_between(p.y, r.upper_left.y, r.lower_right.y)) {

    // normalized ball coordinates within the rectangle
    // [0, 1]
    double nx = (p.x - r.upper_left.x) / (r.lower_right.x - r.upper_left.x);
    double ny = (p.y - r.upper_left.y) / (r.lower_right.y - r.upper_left.y);

    if (modify_angle) {
      double r = getVelocityMagnitude();
      double a = (0.75 - nx / 2) * PI;
      m_ball.velocity = Vector2d(r * cos(a), -r * sin(a));
    } else {
      if (nx < ny == (1 - nx) < ny) {
	m_ball.velocity.y = -m_ball.velocity.y;
      } else {
	m_ball.velocity.x = -m_ball.velocity.x;
      }
    }

    return true;
  }

  return false;
}
