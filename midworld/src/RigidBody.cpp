#include <gmtl/VecOps.h>
#include "RigidBody.h"

namespace mw
{
   void RigidBody::move(float dt)
   {
      gmtl::Vec3f accel = mForce / mMass;
      mVel  += accel * dt;
      mPos  += mVel * dt;      
   }

   void RigidBody::addForce(gmtl::Vec3f force)
   {
      mForce += force;
   }
   
   void RigidBody::addRotForce(gmtl::Vec3f rotForce)
   {      
        mRotForce += rotForce;
   }
   
   void RigidBody::draw()
   {
   
   }
   
   
}
