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
 * File:          $RCSfile: BaseBullet.cpp,v $
 * Date modified: $Date: 2002-10-28 07:41:20 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "BaseBullet.h"

namespace mw
{
   BaseBullet::BaseBullet(GameState* gameState)
      : AbstractEntity(gameState)
      , mExistCount(0)
      , mTimeOut(5)
   {
      mBounds = gmtl::AABoxf(gmtl::Point3f(0,0,0), gmtl::Point3f(0.150f, 0.150f, 0.350f));
   }

   BaseBullet::~BaseBullet()
   {}

   void
   BaseBullet::update(float dt)
   {
      mExistCount += dt;
      Entity::update(dt);
   }

   bool
   BaseBullet::isExpired() const
   {
      return (mExistCount >= mTimeOut);
   }

   void
   BaseBullet::onCollisionEntry(const CollisionEvent& evt)
   {
      if (evt.getSource() == this)
      {
         // Don't collide with other bullets
         if (dynamic_cast<BaseBullet*>(evt.getDesc()->getCollidee()))
         {
            return;
         }
      }
      else
      {
         // Don't collide with other bullets
         if (dynamic_cast<BaseBullet*>(evt.getSource()))
         {
            return;
         }
      }

      // Make sure we die next frame
      mExistCount = mTimeOut;
   }

   void
   BaseBullet::onCollisionMovement(const CollisionEvent& evt)
   {}

   void
   BaseBullet::onCollisionExit(const CollisionEvent& evt)
   {}
}