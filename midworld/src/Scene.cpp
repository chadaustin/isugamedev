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
 * File:          $RCSfile: Scene.cpp,v $
 * Date modified: $Date: 2002-09-17 10:33:09 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <assert.h>
#include <iostream>
#include <algorithm>
#include "Scene.h"
#include "SceneListener.h"

namespace mw
{
   Scene::~Scene()
   {
      std::cerr<<"Bad boy! You didn't clean up your scene."<<std::endl;
   }

   void
   Scene::add(Entity* entity)
   {
      assert(entity != 0);
      assert(mEntities.count(entity->getUID()) == 0);
      mEntities[entity->getUID()] = entity;
      fireEntityAdded(entity);
   }

   void
   Scene::remove(Entity* entity)
   {
      assert(entity != 0);
      EntityMap::iterator itr = mEntities.find(entity->getUID());
      assert(itr != mEntities.end());
      mEntities.erase(itr);
      fireEntityRemoved(entity);
   }

   Entity*
   Scene::get(const Entity::UID& uid)
   {
      EntityMap::iterator itr = mEntities.find(uid);
      if (itr != mEntities.end())
      {
         return itr->second;
      }

      std::cerr<<"ERROR: Unable to retrieve entity from UID: "<<uid<<std::endl;
      return 0;
   }

   Scene::EntityMapCItr
   Scene::begin() const
   {
      return mEntities.begin();
   }

   Scene::EntityMapCItr
   Scene::end() const
   {
      return mEntities.end();
   }

   void
   Scene::addSceneListener(SceneListener* listener)
   {
      mListeners.push_back(listener);
   }

   void
   Scene::removeSceneListener(SceneListener* listener)
   {
     SceneListenerList::iterator itr = std::find(mListeners.begin(),
                                                 mListeners.end(),
                                                 listener);
     if (itr != mListeners.end())
     {
        mListeners.erase(itr);
     }
   }

   void
   Scene::fireEntityAdded(Entity* entity)
   {
      SceneEvent evt(this, entity);
      for (SceneListenerList::iterator itr = mListeners.begin();
           itr != mListeners.end(); ++itr)
      {
         (*itr)->entityAdded(evt);
      }
   }

   void
   Scene::fireEntityRemoved(Entity* entity)
   {
      SceneEvent evt(this, entity);
      for (SceneListenerList::iterator itr = mListeners.begin();
           itr != mListeners.end(); ++itr)
      {
         (*itr)->entityRemoved(evt);
      }
   }
}
