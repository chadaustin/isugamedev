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
 * File:          $RCSfile: AmmoBag.h,v $
 * Date modified: $Date: 2002-10-03 10:47:48 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_AMMO_BAG_H
#define MW_AMMO_BAG_H

#include "Weapon.h"

namespace mw
{
   /**
    * A collection of ammo the player uses to hold all of his ammo. The ammo is
    * organized by category such that multiple weapons of the same category can
    * make use of the same ammo.
    */
   class AmmoBag
   {
   public:
      /// Creates a new ammo bag with no ammo stored on it.
      AmmoBag();

      /// Destroys this ammo bag.
      ~AmmoBag();

      /// Sets the amount of ammo for the given category.
      void set(const Weapon::WeaponCategory& category, unsigned int ammo);

      /// Gets the amount of ammo for the given category.
      unsigned int get(const Weapon::WeaponCategory& category) const;

      /// Adds the given amount of ammo for the given category to this ammo bag.
      void add(const Weapon::WeaponCategory& category, unsigned int ammo);

      /// Removes the given amount of ammo from the given category.
      void remove(const Weapon::WeaponCategory& category, unsigned int ammo);

      /// Adds all the ammo in the given ammo bag into this bag.
      void add(const AmmoBag& bag);

   private:
      /// Our "bag" of bullets.
      unsigned int mAmmo[Weapon::NUM_CATEGORIES];
   };
}

#endif
