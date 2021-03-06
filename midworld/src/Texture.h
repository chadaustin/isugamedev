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
 * File:          $RCSfile: Texture.h,v $
 * Date modified: $Date: 2002-11-25 12:14:24 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_TEXTURE_H
#define MW_TEXTURE_H

#include <string>
#include <SDL_opengl.h>

namespace mw
{
   class Texture
   {
   public:
      Texture(const std::string& filename);
      ~Texture();

      static Texture* create(const std::string& resid);

      void bind();
      static void unbind();
      void drawRectangle(float x1, float y1, float x2, float y2);

   private:
      GLuint mTexture;
      float mRealWidth;
      float mRealHeight;
   };

   template< typename T > struct CachePolicy;

   // Cache policy for Texture objects
   template<>
   struct CachePolicy<Texture*>
   {
      static Texture* copy(Texture* cacheVal)
      {
         return cacheVal;
      }

      static Texture* create(const std::string& name)
      {
         return new Texture(name);
      }

      static void destroy(Texture* val)
      {
         delete val;
      }
   };
}

#endif
