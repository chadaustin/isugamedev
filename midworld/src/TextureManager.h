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
 * File:          $RCSfile: TextureManager.h,v $
 * Date modified: $Date: 2002-10-31 07:03:37 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_IMAGE_MANAGER_H
#define MW_IMAGE_MANAGER_H

#include <map>
#include "Texture.h"

namespace mw
{
   /**
    * The TextureManager is responsible for loading 2D textures from disk and
    * caching them for fast reuse.
    * 
    * <h3>Example: Using the TextureManager</h3>
    * \code
    *    // Create a new texture manager
    *    TextureManager* mgr = new TextureManager();
    *
    *    Texture* chaingun = mgr->get("models/face.png");
    *    Texture* tree = mgr->get("models/smiley.jpeg");
    *
    *    // Don't forget to free memory when we're done!
    *    delete mgr;
    * \endcode
    */
   class TextureManager
   {
   public:
      /// Creates a new TextureManager with an empty cache.
      TextureManager();

      /**
       * Destroys this TextureManager. All allocated textures will be freed and
       * destroyed.
       */
      ~TextureManager();

      /**
       * Gets the texture stored in the given file.
       *
       * @param texture    the name of the file containing the texture to load
       *
       * @return  the texture object; NULL if there was an error
       */
      Texture* get(const std::string& texture);

      /**
       * Preloads the texture stored in the given file and stores it in the cache
       * for later use.
       *
       * @param texture    the name of the file containig the texture to load into
       *                   the cache
       *
       * @return  true if the texture was loaded successfully, false otherwise
       */
      bool preload(const std::string& texture);

      /**
       * Removes all textures contained in the cache.
       */
      void emptyCache();

   private:
      /**
       * Checks the cache for a texture associated with the given name. If a
       * texture is not in the cache, it is created. Otherwise, the texture in
       * the cache is returned.
       *
       * @param texture    the name of the texture to get
       *
       * @return  a texture object for the given name, NULL if it could not be
       *          opened
       */
      Texture* getTexture(const std::string& texture);

   private:
      typedef std::map<std::string, Texture*> TextureCache;

      /// The cache of texture objects
      TextureCache mCache;
   };
}

#endif
