#ifndef STATE_HPP
#define STATE_HPP


struct State {
  virtual ~State() {};

  virtual void draw() {}
  virtual void update(int milliseconds) {}
  virtual void onMouseMove(double x, double y) {}
};


#endif
