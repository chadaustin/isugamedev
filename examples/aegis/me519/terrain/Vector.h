#ifndef VECTOR_H
#define VECTOR_H


#include <GL/glut.h>


class Vector {
public:
  Vector() {
    x = 0;
    y = 0;
    z = 0;
  }

  Vector(const Vector& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
  }

  Vector(float x_, float y_, float z_) {
    x = x_;
    y = y_;
    z = z_;
  }

  float x;
  float y;
  float z;

  Vector operator-() const {
    return Vector(-x, -y, -z);
  }

  Vector& operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  void set(float x_, float y_, float z_) {
    x = x_;
    y = y_;
    z = z_;
  }
};


inline void glTranslate(const Vector& v) {
  glTranslatef(v.x, v.y, v.z);
}


#endif
