#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP


#include <list>
#include "color.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "state.hpp"
#include "vector.hpp"


struct GameState : State {
  enum difficulty {
    EASY,
    MEDIUM,
    HARD
  };

  GameState(difficulty d);

  void draw();
  void update(int milliseconds);
  void onMouseMove(double x, double y);

private:
  void resetBall();
  double getVelocityMagnitude();
  void initializeGL();
  void drawScore();
  void drawGameOver();
  void buildLevel();
  void nextLevel();
  void detectCollisions();
  bool detectCollision(const Rectangle& r, bool modify_angle);

private:
  struct Ball {
    Point2d  position;
    Vector2d velocity;
  };

  struct Block {
    typedef std::list<Block> List;

    Rectangle location;
    Color3d color;
  };

  difficulty m_difficulty;
  double m_paddle;
  Ball m_ball;
  Block::List m_blocks;

  int m_level;
  int m_balls;
  int m_blocks_destroyed;
};


#endif
