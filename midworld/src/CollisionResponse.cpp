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
 * Date modified: $Date: 2002-11-04 19:17:57 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "AmmoCrate.h"
#include "BaseBullet.h"
#include "CollisionResponse.h"
#include "Droid.h"
#include "GunPickup.h"
#include "Player.h"
#include "Turret.h"

namespace mw
{
   void collideBulletPlayer(BaseBullet* b, Player* p)
   {
      b->expire();
//      p->damage(b->getDamage());
      p->damage(1);
   }
   
   void collideBulletEnemy(BaseBullet* b, Enemy* e)
   {
      b->expire();
      e->damage(b->getDamage());
   }
   
   void collideBulletTurret(BaseBullet* b, Turret* t)
   {
      b->expire();
      t->damage(b->getDamage());
   }
   
   void collidePlayerDroid(Player* p, Droid* d)
   {
      __asm int 3
   }
   
   void collidePlayerAmmoCrate(Player* p, AmmoCrate* c)
   {
      c->giveTo(p);
   }
   
   void collidePlayerGunPickup(Player* p, GunPickup* g)
   {
      g->giveTo(p);
   }
   

   CollisionResponse::CollisionResponse()
   {
      defineResponse<BaseBullet, Player>(collideBulletPlayer);
      defineResponse<BaseBullet, Enemy> (collideBulletEnemy);
      defineResponse<BaseBullet, Turret>(collideBulletTurret);
      defineResponse<Player, Droid>(collidePlayerDroid);
      defineResponse<Player, AmmoCrate> (collidePlayerAmmoCrate);
//      defineResponse<Player, GunPickup> (collidePlayerGunPickup);
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
