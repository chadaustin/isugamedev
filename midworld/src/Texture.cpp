/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

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
      for (int y = 0; y < real_height; ++y)
      {
         memcpy(buffer + tex_width * y,
                real_pixels + real_width * y,
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
   Texture::drawRectangle(int x1, int y1, int x2, int y2)
   {
      bind();
      glBegin(GL_TRIANGLE_FAN);
      glVertex2i(x1, y1); glTexCoord2f(0,          0);
      glVertex2i(x2, y1); glTexCoord2f(mRealWidth, 0);
      glVertex2i(x2, y2); glTexCoord2f(mRealWidth, mRealHeight);
      glVertex2i(x1, y2); glTexCoord2f(0,          mRealHeight);
      glEnd();
   }

}
