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
 * File:          $RCSfile: Scene.h,v $
 * Date modified: $Date: 2002-12-21 19:25:49 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_SCENE_H
#define MW_SCENE_H

#include <vector>
#include <set>
#include "Entity.h"

namespace mw
{
   class SceneListener;

   /**
    * Describes the world/scene in which the player is interacting. The scene
    * is essentially a database in which the entities can be looked up by ID.
    */
   class Scene
   {
   public:
      typedef std::set<Entity*>         EntitySet;
      typedef EntitySet::iterator       EntitySetItr;
      typedef EntitySet::const_iterator EntitySetCItr;

   public:
      ~Scene();

      /**
       * Adds the given entity to this scene.
       *
       * @param entity  the entity to add
       * @pre entity != null
       */
      void add(Entity* entity);

      /**
       * Removes the given entity from this scene. If the entity does not exist
       * in this scene, this method returns without error.
       *
       * @param entity  the entity to remove
       * @pre entity != null
       */
      void remove(Entity* entity);

      /**
       * Retrieves the entity in this scene that has the given UID.
       *
       * @param uid     the UID of the entity to get
       *
       * @return  the matching entity; NULL if no entities have the given UID
       */
      //Entity* get(const Entity::UID& uid);

      ///@{
      /**
       * Retrieves an iterator for the entities in this scene at the beginning
       * of the collection.
       *
       * @return  an iterator at the beginning of this scene
       */
      EntitySetItr begin();
      EntitySetCItr begin() const;
      ///@}

      ///@{
      /**
       * Retrieves an iterator for the entities in this scene at the end of the
       * collection.
       *
       * @return  an iterator at the end of this scene
       */
      EntitySetItr end();
      EntitySetCItr end() const;
      ///@}

      /**
       * Adds the given listener to the list of SceneListeners that get notified
       * whenever this scene changes.
       *
       * @param listener        the listener to add
       */
      void addSceneListener(SceneListener* listener);

      /**
       * Removes the given listener from the list of SceneListeners that get
       * notified whenever this scene changes.
       *
       * @param listener        the listener to remove
       */
      void removeSceneListener(SceneListener* listener);

   protected:
      /**
       * Notifies listeners that the given entity was added.
       *
       * @param entity     the entity that was added
       */
      void fireEntityAdded(Entity* entity);

      /**
       * Notifies listeners that the given entity was removed.
       *
       * @param entity     the entity that was removed
       */
      void fireEntityRemoved(Entity* entity);

   private:
      typedef std::vector<SceneListener*> SceneListenerList;

      /**
       * Set of entities in scene.
       */
      EntitySet mEntities;

      /**
       * The list of listeners interested in this scene.
       * @link aggregation
       */
      SceneListenerList mListeners;
   };
}

#endif
