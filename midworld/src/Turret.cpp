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
 * Date modified: $Date: 2002-10-29 11:02:07 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include "Turret.h"
#include "SpreadGun.h"

#include <gmtl/Math.h>
#include <iostream>

namespace mw
{
   Turret::Turret(GameState* gameState)
      : Enemy(gameState)
   {
      gun = new SpreadGun();
   }

   
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
   
   Weapon* Turret::getGun()
   {
      return gun;
   }

   void Turret::shoot()
   {
      gun->trigger(true);
   }
}
