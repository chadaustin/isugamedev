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
 * Date modified: $Date: 2002-10-09 06:57:19 $
 * Version:       $Revision: 1.4 $
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
      gmtl::Vec3f force;
      if (rand() % 100 < 10)
      {
         int x = rand() % randRange;
         int y = rand() % randRange;

         switch (rand() % 4)
         {
            case 0: force.set( x, 0,  y); break;
            case 1: force.set(-x, 0,  y); break;
            case 2: force.set( x, 0, -y); break;
            case 3: force.set(-x, 0, -y); break;
         }
         addForce(force);
      }
      if ((rand() % 100) == 0)
      {
         gmtl::Quatf nRot = gmtl::makeRot<gmtl::Quatf>(
            gmtl::AxisAnglef(rand() % randRange, 0, 1, 0));
         setRot(nRot);
      }
      RigidBody::update(timeDelta);
   }
}
