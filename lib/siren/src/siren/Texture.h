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
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,                                                                                               
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Texture.h,v $
 * Date modified: $Date: 2003-02-22 23:53:34 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_TEXTURE_H
#define SIREN_TEXTURE_H

#include <string>
#include "Export.h"
#include "OpenGL.h"


namespace siren
{
   /**
    * Your basic OpenGL texture.
    */
   class SIREN_CLASS Texture
   {
   public:
      /**
       * Creates a new texture based on the image found in the given file.
       *
       * @param filename      The name of the image file
       *
       * @throw std::runtime_error     if there was a problem loading the image
       */
      Texture(const std::string& filename);

      /**
       * Creates a new blank texture of the given size. It will have the given
       * number of channels and be of the given OpenGL type.
       */
      Texture(unsigned int width, unsigned int height, int channels, int type);

      ~Texture();

      /**
       * Creates the texture assigned to the given resource ID. The texture will
       * be retrieved from the resource manager.
       *
       * @see ResourceManager
       */
      static Texture* create(const std::string& resid);

      /**
       * Binds this texture to be used for future fragments.
       */
      void bind();

      /**
       * Unbinds the current texture.
       */
      static void unbind();

      void drawRectangle(float x1, float y1, float x2, float y2);

      int getTexWidth() const;
      int getTexHeight() const;

      GLuint getTextureID() const;

   private:
      GLuint mTexture;
      float mRealWidth;
      float mRealHeight;
      int mTexWidth;
      int mTexHeight;
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
