/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "Enemy.h"
#include <gmtl/Quat.h>
#include <gmtl/Vec.h>
#include <gmtl/Generate.h>
#include "cubeGeometry.h"
#include <GL/gl.h>
#include <cstdlib>

namespace mw
{

   //@TODO:  Do something other than randomly change velocity and rotation :P
   void Enemy::update(float timeDelta)
   {
      unsigned int randRange = 5;
      gmtl::Vec3f nVel;
      if (rand() % 100 < 10)
      {
         switch(rand() % 3)
         {
            case 0:
               nVel.set(static_cast<float>(rand() % randRange),0,
                             static_cast<float>(rand() % randRange));
               break;
            case 1:
               nVel.set(-(static_cast<float>(rand() % randRange)),0,
                             static_cast<float>(rand() % randRange));
               break;
            case 2:
               nVel.set(static_cast<float>(rand() % randRange),0,
                             -(static_cast<float>(rand() % randRange)));
               break;
            case 3:
               nVel.set(-(static_cast<float>(rand() % randRange)),0,
                             -(static_cast<float>(rand() % randRange)));
               break;
            default:
               std::cerr << "Rand generated a random error." << std::endl;
         }
         this->setVel(nVel);
      }
      if ( (rand() % 100) < 1)
      {
         gmtl::Quatf nRot = gmtl::makeRot<gmtl::Quatf>(gmtl::AxisAnglef(
                       static_cast<float>(rand() % randRange), 0, 1, 0));
         this->setRot(nRot);
      }
      RigidBody::update(timeDelta);
   }

   //@TODO:  Draw something other than the standard cubes.
   void Enemy::draw() const
   {
      gmtl::Point3f pos = this->getPos();
      gmtl::Quatf rot = this->getRot();
      glPushMatrix();
         glTranslatef(pos[0], pos[1], pos[2]);
         glMultMatrixf( gmtl::make<gmtl::Matrix44f>( rot ).getData() );
         glScalef(0.5f, 0.5f, 0.5f);
         cubeGeometry().render();
      glPopMatrix();
   }

}//end of namespace mw
