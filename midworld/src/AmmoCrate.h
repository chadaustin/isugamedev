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
 * File:          $RCSfile: AmmoCrate.h,v $
 * Date modified: $Date: 2002-10-03 10:47:48 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_AMMO_CRATE_H
#define MW_AMMO_CRATE_H

#include "PickupItem.h"

namespace mw
{
   /**
    * Defines a pickup item containing a bunch of ammo.
    */
   class AmmoCrate : public PickupItem
   {
   public:
      AmmoCrate();

      /**
       * Sets the amount of ammo for the given weapon category that is stored in
       * this ammo crate.
       */
      void setAmmo(const Weapon::WeaponCategory& category, unsigned int ammo);

      /**
       * Gets the amount of ammo for the given weapon category that is stored in
       * this ammo crate.
       */
      unsigned int getAmmo(const Weapon::WeaponCategory& category) const;

      /**
       * The ammo crate expires once it has been picked up.
       */
      bool isExpired() const;

   protected:
      /**
       * Notifies this pickup item that it has been picked up by the given
       * player.
       *
       * @param player     the player that picked up the item
       */
      void pickedUp(Player* player);

   private:
      /// The ammo stored in this crate.
      AmmoBag mAmmoBag;

      /// Flag for if this ammo has expired.
      bool mExpired;
   };
}

#endif
