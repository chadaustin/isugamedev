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
 * File:          $RCSfile: Shotgun.cpp,v $
 * Date modified: $Date: 2002-09-09 00:56:25 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/Math.h>
#include <stdlib.h>
#include <SDL.h>
#include "Shotgun.h"
#include "cubeGeometry.h"
#include "GameState.h"

const static unsigned int NUM_PELLETS = 10;

namespace mw
{
   Shotgun::Shotgun()
      : BaseProjectileWeapon(Weapon::RIFLE, "Shotgun")
   {
      mSpreadAngle = 10.0f;
      mMaxAmmoInBag = 1200;
      mClipSize = 6;

      mReloadRate = 2.0f;
      mCockRate = 0.7f;

      mAmmoInClip = mClipSize;
      mAmmoInBag = 100;

      srand(SDL_GetTicks());
   }

   void Shotgun::draw() const
   {
      glPushMatrix();
         glMultMatrixf(this->matrix().getData());
         glScalef(0.15f, 0.15f, 0.8f);
         cubeGeometry().render();
      glPopMatrix();
   }

   void Shotgun::discharge(GameState& g)
   {
      // add the bullet to the gamestate...
      for(unsigned int i=0; i<NUM_PELLETS; i++)
      {
         //TODO:  seed this according to world time?


         //generate random bullet directions with the sweep of mSpreadAngle
         //degrees
         float angle = gmtl::Math::deg2Rad((mSpreadAngle* float(rand())/RAND_MAX) - (mSpreadAngle/2));

         gmtl::Quatf r(gmtl::make<gmtl::Quatf>(gmtl::AxisAnglef(angle, 0.0f, 1.0f, 0.0f)));

         BaseBullet* bullet = this->createBullet();

         bullet->setRot(this->getRot() * r); //shoot off at a limited random angle
         bullet->setPos(this->getPos());
         bullet->setVel(this->getRot() * r * bullet->getVel());

         g.add(bullet); // bullet is not mine anymore, belongs to GameState

      }
   }

   void Shotgun::ejectCasing(GameState& g)
   {
      /// @todo eject a casing into the game
   }
}
