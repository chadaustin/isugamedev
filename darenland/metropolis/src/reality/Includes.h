#include <stdlib.h>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <assert.h>

//gmtl math stuff
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>



//we are going to differentiate between vectors and points, so the standard is, use Vec3f and Point3f wherever
//possible instead of Vec4f with the W value set. This will keep things clearer for everyone.
//Points should be all positions and basically all properties that can be translated.
//Vectors are things like velocities and accelerations, things that have direction but will not be translated by
//matrices or otherwise.

#include <gmtl/Point.h>


#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>

#include <boost/shared_ptr.hpp> // smart pointers are good

#include "Defines.h"

//we may need to specify the order
//in which openGL headers get included.
//for instance glext.h wants to be included
//before gl.h or anything openGL related.
#include <GL/glut.h>
