#ifndef MATH_H
#define MATH_H


#include <math.h>


static const float PI = 3.1415927;

inline float DegreesToRadians(float v) {
  return PI * v / 180;
}

inline float RadiansToDegrees(float v) {
  return 180 * v / PI;
}

inline int Floor(float v) {
  return (int)floor(v);
}

inline int Ceiling(float v) {
  return (int)ceil(v);
}


#endif
