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
 * File:          $RCSfile: ModelManager.cpp,v $
 * Date modified: $Date: 2002-10-09 08:09:39 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <list>
#include <OpenSG/OSGSceneFileHandler.h>
#include "ModelManager.h"

namespace mw
{
   ModelManager::ModelManager()
   {
      typedef std::list<const char*> SuffixList;
      SuffixList suffixes;
      osg::SceneFileHandler::the().getSuffixList(suffixes);

      std::cout<<"ModelManager supports the following file formats:"<<std::endl;
      for(SuffixList::iterator itr = suffixes.begin(); itr != suffixes.end(); ++itr)
      {
         std::cout<<"\t"<<(*itr)<<std::endl;
      }
   }

   ModelManager::~ModelManager()
   {
   }

   osg::NodePtr
   ModelManager::get(const std::string& model)
   {
      return getModel(model);
   }

   bool
   ModelManager::preload(const std::string& model)
   {
      return (getModel(model) != osg::NullFC);
   }

   void
   ModelManager::emptyCache()
   {
      mCache.clear();
   }

   osg::NodePtr
   ModelManager::getModel(const std::string& model)
   {
      // Check the cache first
      ModelCache::iterator itr = mCache.find(model);

      // Cache hit. Return a clone of the tree in the cache
      if (itr != mCache.end())
      {
         return osg::cloneTree(itr->second);
      }
      // Cache miss. Open the model and cache it
      else
      {
         std::cout<<"ModelManager: Cache miss of '"<<model<<"'"<<std::endl;
         osg::NodePtr model_node = osg::SceneFileHandler::the().read(model.c_str());
         if (model_node != osg::NullFC)
         {
            mCache[model] = model_node;
            return osg::cloneTree(model_node);
         }
         return osg::NullFC;
      }
   }
}
