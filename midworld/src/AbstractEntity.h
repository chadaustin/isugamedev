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
 * File:          $RCSfile: AbstractEntity.h,v $
 * Date modified: $Date: 2002-09-07 06:39:13 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_ABSTRACT_ENTITY_H
#define MW_ABSTRACT_ENTITY_H

#include "UIDManager.h"
#include "Entity.h"

namespace mw
{
   /**
    * Provides an abstract base implementation of Entity that handles the stuff
    * common to virtually every Entity implementation. This includes automatic
    * unique ID management as well as model ID management.
    */
   class AbstractEntity : public Entity
   {
   protected:
      /**
       * Initializes this abstract entity with a new unique ID.
       */
      AbstractEntity();

      /**
       * Destroys this abstract entity and releases the unique ID it had
       * reserved.
       */
      virtual ~AbstractEntity();

   public:
      /**
       * Gets the ID of the model this entity requires.
       */
      int getModel() const;

      /**
       * Sets the ID of the model this entity requires.
       */
      void setModel(int model);

      /**
       * Gets the unique ID of this entity.
       */
      const UID& getUID() const;

   private:
      /**
       * The unique ID associated with this entity.
       */
      UID mUID;

      /**
       * The model ID this entity uses.
       */
      int mModel;
   };
}

#endif
