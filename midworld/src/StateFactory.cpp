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
 * File:          $RCSfile: StateFactory.cpp,v $
 * Date modified: $Date: 2002-10-01 04:21:38 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include <stdexcept>
#include "StateFactory.h"
#include "State.h"

namespace mw
{
   StateFactory* StateFactory::mSingleton = 0;
   
   StateFactory::StateFactory()
   {}

   StateFactory::~StateFactory()
   {}

   StateFactory& StateFactory::getInstance()
   {
      if (mSingleton == 0)
      {
         mSingleton = new StateFactory();
         atexit(destroyInstance);
      }
      return *mSingleton;
   }

   State*
   StateFactory::create(const std::string& name, Application* app)
   {
      CreatorMap::iterator itr = mCreators.find(name);
      if (itr != mCreators.end())
      {
         return itr->second->create(app);
      }
      else
      {
         throw std::runtime_error("Could not instantiate state: " + name);
      }
   }

   void
   StateFactory::registerCreator(const std::string& name, StateCreator* creator)
   {
      std::cout<<"Registering state: "<<name<<std::endl;
      CreatorMap::iterator itr = mCreators.find(name);
      if (itr != mCreators.end())
      {
         delete itr->second;
         mCreators.erase(itr);
      }

      mCreators[name] = creator;
   }

   void
   StateFactory::unregisterCreator(const std::string& name)
   {
      CreatorMap::iterator itr = mCreators.find(name);
      if (itr != mCreators.end())
      {
         delete itr->second;
         mCreators.erase(itr);
      }
   }

   void
   StateFactory::destroyInstance()
   {
      delete mSingleton;
   }
}
