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
 * File:          $RCSfile: BaseBullet.h,v $
 * Date modified: $Date: 2002-10-31 08:35:57 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_BASE_BULLET_H
#define MW_BASE_BULLET_H

#include "AbstractEntity.h"

namespace mw
{
   /**
    * This class represents the base bullet from which all guns derive
    * their bullet types.
    */
   class BaseBullet: public AbstractEntity
   {
   public:
      /**
       * Constructor
       */
      BaseBullet(GameState* gameState);

      /**
       * Destructor
       */
      ~BaseBullet();

      /**
       * Update this bullet based on the time that has passed.
       * @param dt the amount of time in seconds that has passed
       */
      virtual void update(float dt);

      bool isExpired() const;

   protected:
      /// The amount of time that this bullet has existed in the GameState
      float mExistCount;

      /// The amount of time this bullet is allowed to stay in the GameState
      float mTimeOut;
   };
}

#endif
