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
 * File:          $RCSfile: Pistol.h,v $
 * Date modified: $Date: 2002-10-01 04:26:42 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_PISTOL_H
#define MW_PISTOL_H

#include <gmtl/Math.h>
#include "BaseProjectileWeapon.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class Pistol : public BaseProjectileWeapon
   {
   public:
      Pistol()
         : BaseProjectileWeapon( Weapon::HANDGUN, "Pistol" )
      {}

      /** render the weapon using opengl calls. */
      void draw() const 
      {
         glPushMatrix();
            glMultMatrixf(matrix().getData());
            glScalef( 0.15f, 0.15f, 0.3f );
            cubeGeometry().render();
         glPopMatrix();
      }

      // some of these will change to public...
   protected:
      void discharge(GameState& g)
      {
         // add the bulllet to the gamestate...
         BaseBullet* bullet = createBullet("bullet");
         bullet->setRot(getRot());
         bullet->setPos(getPos());
         bullet->setVel(getRot() * bullet->getVel());
         g.add(bullet); // bullet is not mine anymore, belongs to GameState
      }

      void ejectCasing(GameState& g)
      {
         /// @todo eject a casing
      }
   };
}

#endif
