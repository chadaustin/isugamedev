#ifndef POINT_HPP
#define POINT_HPP


#include "tuple.hpp"
#include "vector.hpp"


struct Point2d : Tuple2d {
  Point2d(double x = 0, double y = 0)
    : Tuple2d(x, y) { }
};


inline Point2d& operator+=(Point2d& lhs, const Vector2d& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}


#endif
