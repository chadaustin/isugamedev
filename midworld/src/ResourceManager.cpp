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
 * File:          $RCSfile: ResourceManager.cpp,v $
 * Date modified: $Date: 2002-11-25 10:08:03 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "ResourceManager.h"
#include "Texture.h"

namespace mw
{
   ResourceManager::ResourceManager()
   {
      // load the model mappings
      std::ifstream in("resources.txt");
      if (in.is_open())
      {
         std::string name, model;
         while (in >> name >> model)
         {
            defineResourceID(name, model);
         }
      }

      defineFactory<Texture*>(&createTexture);
   }

   ResourceManager::~ResourceManager()
   {}

   const std::string&
   ResourceManager::lookup(const std::string& resid) const
   {
      if (resid.empty()) {
         static const std::string empty;
         return empty;
      }
   
      ResourceIDMap::const_iterator itr = mResourceIDs.find(resid);
      if (itr != mResourceIDs.end())
      {
         return itr->second;
      }
      std::cout << resid << std::endl;
      throw std::runtime_error("Invalid ResourceID");
   }

   void
   ResourceManager::defineResourceID(const std::string& resid, const std::string& value)
   {
      ResourceIDMap::iterator itr = mResourceIDs.find(resid);
      if (itr == mResourceIDs.end())
      {
         mResourceIDs[resid] = value;
      }
      else
      {
         throw std::runtime_error("ResourceID already in use");
      }
   }

   void
   ResourceManager::removeResourceID(const std::string& resid)
   {
      ResourceIDMap::iterator itr = mResourceIDs.find(resid);
      if (itr != mResourceIDs.end())
      {
         std::cout<<"Removed Resource: "<<resid<<" -> "<<(itr->second)<<std::endl;
         mResourceIDs.erase(itr);
      }
      else
      {
         throw std::runtime_error("Invalid ResourceID");
      }
   }

   ResourceManager::Cache&
   ResourceManager::getCache(const Loki::TypeInfo& type)
   {
      CacheMap::iterator itr = mCaches.find(type);
      if (itr != mCaches.end())
      {
         return itr->second;
      }
      else
      {
         // Cache doesn't exist, create it now
         mCaches[type] = Cache();
         return mCaches[type];
      }
   }

   ResourceManager::Factory
   ResourceManager::getFactory(const Loki::TypeInfo& type)
   {
      FactoryMap::iterator itr = mFactories.find(type);
      if (itr != mFactories.end())
      {
         return itr->second;
      }
      else
      {
         return 0;
      }
   }
}
