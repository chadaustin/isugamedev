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
 * File:          $RCSfile: Turret.cpp,v $
 * Date modified: $Date: 2003-06-16 08:14:56 $
 * Version:       $Revision: 1.16 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include <gmtl/Math.h>
#include "EntityFactory.h"
#include "SpreadGun.h"
#include "Turret.h"
//#include "ParticleEngine.h"

namespace mw
{
   Turret::Turret(GameState* gameState)
      : Enemy(gameState)
   {
      gun = new SpreadGun();
      gun->setSource("Turret");
   }
   
   
   Turret::~Turret()
   {
/*      EntityFactory& factory = EntityFactory::instance();
      ParticleEngine* engine = new ParticleEngine(
         factory.getGameState(),
         "explosive_particle",
         1000);
      factory.add(engine);
      
      engine->setPos(getPos());
*/   }

   
   void Turret::aim()
   {
   
   }

   float Turret::getTimeDelta()
   {
      return timeDelta;
   }
   
   void Turret::update(float dt)
   {
      timeDelta = dt;
      Enemy::update(dt);
      gun->update(*getGameState(), dt);
      gun->trigger(false);
   }
   
   void Turret::shoot()
   {
      gun->trigger(true);
   }

   Weapon* Turret::getGun()
   {
      return gun;
   }
}
