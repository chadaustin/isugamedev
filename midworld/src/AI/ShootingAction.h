#ifndef MW_SHOOTING_ACTION_H
#define MW_SHOOTING_ACTION_H

#include <iostream>
#include <gmtl/Matrix.h>
#include <gmtl/Quat.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>
#include <gmtl/Math.h>
#include "../EnemyUnit.h"
#include "ActionContainer.h"
#include "AINode.h"


namespace mw
{


class ShootingAction : public ActionContainer
{
public:
   ShootingAction()
   {
   };

   virtual void Perform()
   {
      gmtl::Vec3f mPos;
      float randNum = gmtl::Math::unitRandom();
      mPos[0] = randNum;
      randNum = gmtl::Math::unitRandom();
      mPos[1] = randNum;
      randNum = gmtl::Math::unitRandom();
      mPos[2] = randNum;
      AINode::getUnit()->translate(mPos);
   }

private:
};

}



#endif
