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
 * File:          $RCSfile: AmmoCrate.cpp,v $
 * Date modified: $Date: 2002-11-04 19:17:57 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <algorithm>
#include "AmmoCrate.h"
#include "Player.h"

namespace mw
{
   AmmoCrate::AmmoCrate(GameState* gameState)
      : AbstractEntity(gameState)
      , mExpired(false)
   {
   }

   void
   AmmoCrate::setAmmo(const Weapon::WeaponCategory& category, unsigned int ammo)
   {
      mAmmoBag.set(category, ammo);
   }

   unsigned int
   AmmoCrate::getAmmo(const Weapon::WeaponCategory& category) const
   {
      return mAmmoBag.get(category);
   }

   bool
   AmmoCrate::isExpired() const
   {
      return mExpired;
   }

   void
   AmmoCrate::giveTo(Player* player)
   {
      std::cout<<"Player picked up the ammo bag!"<<std::endl;
      player->getAmmoBag().add(mAmmoBag);
      mExpired = true;
   }
}
