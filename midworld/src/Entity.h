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
 * File:          $RCSfile: Entity.h,v $
 * Date modified: $Date: 2002-10-31 08:35:59 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_ENTITY_H
#define MW_ENTITY_H

#include "RigidBody.h"

namespace mw
{
   /**
    * An entity is a specialized type of rigid body from which all objects with
    * which the player may interact derive from. This includes enemies,
    * projectiles, doors, ammo crates, etc.
    */
   class Entity : public RigidBody
   {
   public:
      /**
       * The UID data type.
       */
      typedef unsigned long UID;

      virtual ~Entity() {}
      
      virtual void draw() const = 0;

      /**
       * Determines if this entity has expired and needs to be removed from the
       * game. This allows all expired objects to be removed in a single pass at
       * the end of each frame.
       *
       * @return  true if this entity wishes to be removed from the game; false
       *          otherwise
       */
      virtual bool isExpired() const = 0;

      /**
       * Gets the ID of the model this entity requires.
       */
      virtual const std::string& getModel() const = 0;

      /**
       * Sets the ID of the model this entity requires.
       */
      virtual void setModel(const std::string& model) = 0;

      /**
       * Gets the unique ID of this entity.
       */
      virtual const UID& getUID() const = 0;
   };
}

#endif
