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
 * Date modified: $Date: 2002-11-01 12:14:51 $
 * Version:       $Revision: 1.10 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#include <gmtl/Quat.h>
#include <gmtl/Vec.h>
#include <gmtl/Generate.h>
#include <SDL_opengl.h>
#include <cstdlib>
#include "Enemy.h"
#include "EntityFactory.h"
#include "ParticleEngine.h"
#include "Pistol.h"

namespace mw
{

   Enemy::Enemy(GameState* gameState)
      : AbstractEntity(gameState)
      , mHealth(100)
   {
      gun = new Pistol;
   }
   
   Enemy::~Enemy()
   {
      EntityFactory& factory = EntityFactory::instance();
      ParticleEngine* engine = new ParticleEngine(
         factory.getGameState(),
         "images/explosive_particle.png",
         500);
      factory.add(engine);
     
      engine->setPos(getPos());
   }

   void Enemy::update(float timeDelta)
   {
/*
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
*/
      gun->update(*getGameState(), timeDelta);
      RigidBody::update(timeDelta);
 //     gun->trigger(false);
   }

   void Enemy::walkRandom()
   {

      std::cout << "in Walk Random" << std::endl;
      if (rand() % 100 < 5)
      {
         gmtl::Vec3f force = randomUnitVector() * 5;
         force[1] = 0;  // no vertical forces
         addForce(force);
      }
      if ((rand() % 100) == 0)
      {

         gmtl::Quatf nRot = gmtl::makeRot<gmtl::Quatf>(
            gmtl::AxisAnglef(3.141/2.0, 0, 1, 0));
         setRot(nRot);
      }
   }
      
   
}
