#ifndef UTILITY_H
#define UTILITY_H


#include <GL/gl.h>
#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>


inline void glMultMatrix(const gmtl::Matrix44f& m) {
    glMultMatrixf(m.mData);
}

inline void glTranslate(const gmtl::Vec3f& v) {
    glTranslatef(v[0], v[1], v[2]);
}


#endif
