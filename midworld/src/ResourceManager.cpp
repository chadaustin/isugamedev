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
 * Date modified: $Date: 2002-09-23 03:56:25 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <stdexcept>
#include <iostream>
#include "ResourceManager.h"

namespace mw
{
   ResourceManager::ResourceManager()
   {
   }

   ResourceManager::~ResourceManager()
   {
   }

   const std::string&
   ResourceManager::get(const std::string& resid) const
   {
//      std::cout<<"Getting resource: "<<resid<<std::endl;
      ResourceMap::const_iterator itr = mResources.find(resid);
      if (itr != mResources.end())
      {
         return itr->second;
      }
      throw std::runtime_error("Invalid ResourceID");
   }

   void
   ResourceManager::add(const std::string& resid, const std::string& value)
   {
      ResourceMap::iterator itr = mResources.find(resid);
      if (itr == mResources.end())
      {
         mResources[resid] = value;
         std::cout<<"Added Resource: "<<resid<<" -> "<<value<<std::endl;
      }
      else
      {
         throw std::runtime_error("ResourceID already in use");
      }
   }

   void
   ResourceManager::remove(const std::string& resid)
   {
      ResourceMap::iterator itr = mResources.find(resid);
      if (itr != mResources.end())
      {
         std::cout<<"Removed Resource: "<<resid<<" -> "<<(itr->second)<<std::endl;
         mResources.erase(itr);
      }
      else
      {
         throw std::runtime_error("Invalid ResourceID");
      }
   }
}
