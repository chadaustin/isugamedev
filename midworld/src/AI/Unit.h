#ifndef UNIT
#define UNIT

#include <math.h>
#include <iostream>
#include "behaviorMachine.h"
#include <vector>
/*
#include <gmtl/Matrix.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>
*/


class unit
{
public:
	unit(){};
   void GetPos(float &x, float &y, float &z)
   { 
      x = pos[0];
      y = pos[1];
      z = pos[2];
   }
   void SetPos(const float &x, const float &y, const float &z)
   {
      pos[0] = x;
      pos[1] = y;
      pos[2] = z;
   }
   
   void GetRot(float &x, float &y, float &z)
   { 
      x = rot[0];
      y = rot[1];
      z = rot[2];
   }
   void SetRot(const float &x, const float &y, const float &z)
   {
      rot[0] = x;
      rot[1] = y;
      rot[2] = z;
   }
   
   

private:
   float pos[3];
   float rot[3];
};

#endif 