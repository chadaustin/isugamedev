#ifndef VECTOR_HPP
#define VECTOR_HPP


#include "tuple.hpp"


struct Vector2d : Tuple2d {
  Vector2d(double x = 0, double y = 0)
    : Tuple2d(x, y) { }
};


inline Vector2d operator*(double scalar, const Vector2d& v) {
  return Vector2d(scalar * v.x, scalar * v.y);
}


#endif
