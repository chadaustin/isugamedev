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
 * File:          $RCSfile: Texture.cpp,v $
 * Date modified: $Date: 2002-09-23 21:25:23 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#include <iostream>
#include <memory>
#include <stdexcept>
#include <corona.h>
#include "Texture.h"
#include "Types.h"
#include "Utility.h"
using namespace corona;


namespace mw
{

   int GetNextPowerOf2(int n)
   {
      int i = 1;
      while (i < n)
      {
         i *= 2;
      }
      return i;
   }


   inline void ThrowTextureError(const std::string error)
   {
      throw std::runtime_error(error.c_str());
   }


   Texture::Texture(const std::string& filename)
   {
      std::auto_ptr<Image> image(
         OpenImage(filename.c_str(), FF_AUTODETECT, PF_R8G8B8A8));
      if (!image.get())
      {
         ThrowTextureError("Could not load image '" + filename + "'");
      }

      // remember the actual size of the image so we know how much of the
      // texture to use when calculating texture coordinates
      int  real_width  = image->getWidth();
      int  real_height = image->getHeight();
      u32* real_pixels = (u32*)image->getPixels();

      // allocate power of two buffer to store actual texture memory
      // and zero it
      int tex_width  = GetNextPowerOf2(real_width);
      int tex_height = GetNextPowerOf2(real_height);
      u32* buffer = new u32[tex_width * tex_height];
      memset(buffer, 0, tex_width * tex_height * sizeof(u32));

      /// @todo  make sure we don't try to create a texture that
      ///        larger than what the video card can handle...
      ///        3Dfx cards can only handle 256*256 tex's

      // copy our image pixels into the texture buffer
      for (int row = 0; row < real_height; ++row)
      {
         memcpy(buffer + tex_width * row,
                real_pixels + real_width * row,
                real_width * sizeof(u32));
      }

      mRealWidth  = float(real_width)  / tex_width;
      mRealHeight = float(real_height) / tex_height;

      glGenTextures(1, &mTexture);
      glBindTexture(GL_TEXTURE_2D, mTexture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                   tex_width, tex_height,
                   0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      /// @todo  use a boost scoped array
      delete[] buffer;
   };


   Texture::~Texture()
   {
      glDeleteTextures(1, &mTexture);
   }


   void
   Texture::bind()
   {
      glBindTexture(GL_TEXTURE_2D, mTexture);
   }


   void
   Texture::drawRectangle(float x1, float y1, float x2, float y2)
   {
      bind();
      glBegin(GL_QUADS);
      glTexCoord2f(0,          0);           glVertex2f(x1, y1);
      glTexCoord2f(mRealWidth, 0);           glVertex2f(x2, y1); 
      glTexCoord2f(mRealWidth, mRealHeight); glVertex2f(x2, y2); 
      glTexCoord2f(0,          mRealHeight); glVertex2f(x1, y2); 
      glEnd();
   }

}
