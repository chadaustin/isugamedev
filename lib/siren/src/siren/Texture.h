/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * Date modified: $Date: 2003-02-06 07:20:30 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_TEXTURE_H
#define SIREN_TEXTURE_H

#include <string>

namespace siren
{
   /**
    * Your basic OpenGL texture.
    */
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

   /**
    * Cache policy for Texture objects so that they can be used with the
    * ResourceManager system.
    */
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
