#ifndef NULL_STATE_HPP
#define NULL_STATE_HPP


#include "state.hpp"


struct NullState : State {
  void draw();
  void update(int) {}
  void onMouseMove(double, double) {}
};


#endif
