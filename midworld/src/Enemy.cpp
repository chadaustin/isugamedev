/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Enemy.cpp,v $
 * Date modified: $Date: 2002-07-07 02:21:10 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

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
