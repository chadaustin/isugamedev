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
 * File:          $RCSfile: SceneEvent.h,v $
 * Date modified: $Date: 2002-09-17 10:33:09 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_SCENE_EVENT_H
#define MW_SCENE_EVENT_H

#include "Scene.h"

namespace mw
{
   class SceneEvent
   {
   public:
      /**
       * Creates a new scene event for the given scene and entity.
       *
       * @param scene       the scene that fired the event
       * @param entity      the entity about which this event revolves
       */
      SceneEvent(Scene* scene, Entity* entity);

      /**
       * Gets the scene that fired off the event.
       */
      Scene* getScene() const;

      /**
       * Gets the entity associated with this event.
       */
      Entity* getEntity() const;

   private:
      Scene* mScene;
      Entity* mEntity;
   };
}

#endif
