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
 * File:          $RCSfile: TextureManager.cpp,v $
 * Date modified: $Date: 2002-10-31 07:03:37 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include <stdexcept>
#include "TextureManager.h"

namespace mw
{
   TextureManager::TextureManager()
   {}

   TextureManager::~TextureManager()
   {
   }

   Texture*
   TextureManager::get(const std::string& texture)
   {
      return getTexture(texture);
   }

   bool
   TextureManager::preload(const std::string& texture)
   {
      return (getTexture(texture) != 0);
   }

   void
   TextureManager::emptyCache()
   {
      mCache.clear();
   }

   Texture*
   TextureManager::getTexture(const std::string& texture)
   {
      // Check the cache first
      TextureCache::iterator itr = mCache.find(texture);

      // Cache hit.
      if (itr != mCache.end())
      {
         return itr->second;
      }
      // Cache miss. Open the texture and cache it
      else
      {
         std::cout<<"[TextureManager] Cache miss for '"<<texture<<"'"<<std::endl;

         try
         {
            Texture* tex = new Texture(texture);
            mCache[texture] = tex;
            return tex;
         }
         catch (const std::runtime_error& e)
         {
            return 0;
         }
      }
   }
}
