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
 * File:          $RCSfile: CollisionResponse.cpp,v $
 * Date modified: $Date: 2002-11-14 11:57:28 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "AmmoCrate.h"
#include "BaseBullet.h"
#include "CollisionResponse.h"
#include "Droid.h"
#include "GunPickup.h"
#include "Player.h"
#include "StaticEntity.h"
#include "Turret.h"
#include "Utility.h"

namespace mw
{
   void collideBulletPlayer(BaseBullet* b, Player* p)
   {
      b->expire();
      if (b->getSource() != "Player") {
         p->damage(1);
      }
   }
   
   void collideBulletDroid(BaseBullet* b, Droid* d)
   {
      b->expire();
      if (b->getSource() != "Droid") {
         d->damage(b->getDamage());
      }
   }
   
   void collideBulletTurret(BaseBullet* b, Turret* t)
   {
      b->expire();
      if (b->getSource() != "Turret") {
         t->damage(b->getDamage());
      }
   }
   
   void collidePlayerAmmoCrate(Player* p, AmmoCrate* c)
   {
      c->giveTo(p);
   }
   
   void collidePlayerGunPickup(Player* p, GunPickup* g)
   {
      g->giveTo(p);
   }


   void collideBulletStatic(BaseBullet* b, StaticEntity*)
   {
      b->expire();
   }


   void collideBulletAmmo(BaseBullet* b, AmmoCrate*)
   {
      b->expire();
   }
   

   CollisionResponse::CollisionResponse()
   {
      defineResponse<BaseBullet, Player>(collideBulletPlayer);
      defineResponse<BaseBullet, Droid> (collideBulletDroid);
      defineResponse<BaseBullet, Turret>(collideBulletTurret);
      defineResponse<Player, AmmoCrate> (collidePlayerAmmoCrate);
      defineResponse<Player, GunPickup> (collidePlayerGunPickup);
      defineResponse<BaseBullet, StaticEntity>(collideBulletStatic);
      defineResponse<BaseBullet, AmmoCrate>(collideBulletAmmo);
      
      setCollidable<BaseBullet, BaseBullet>    (false);
      setCollidable<StaticEntity, StaticEntity>(false);
      setCollidable<Turret, Turret>            (false);
      setCollidable<Turret, StaticEntity>      (false);
   }
   
   CollisionResponse::~CollisionResponse()
   {
      for (ResponseMap::iterator i = mResponseMap.begin();
           i != mResponseMap.end();
           ++i)
      {
         delete i->second;
      }
   }
}
