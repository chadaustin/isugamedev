#include <iostream>
#include <memory>
#include <stdexcept>
#include <corona.h>
#include "Texture.h"
#include "Types.h"
using namespace corona;


namespace lr 
{
   static GLuint gHighID = 10000;

   int GetNextPowerOf2(int n)
   {
      int i = 1;
      while (i < n)
      {
         i *= 2;
      }
      return i;
   }


   inline void ThrowTextureError(const std::string& error)
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

      // XXX THIS SUCKS ASS!
      // Use our own high integers for texture IDs so that we can play friendly
      // with OpenSG' textures.
//      glGenTextures(1, &mTexture);
      mTexture = gHighID++;
      glBindTexture(GL_TEXTURE_2D, mTexture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                   tex_width, tex_height,
                   0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      delete[] buffer;
   };


   Texture::~Texture()
   {
      glDeleteTextures(1, &mTexture);
   }

   Texture*
   Texture::create(const std::string& resid)
   {
      return new Texture(resid);
   }

   void
   Texture::bind()
   {
      glBindTexture(GL_TEXTURE_2D, mTexture);
   }

   
   void
   Texture::unbind()
   {
      glBindTexture(GL_TEXTURE_2D, 0);
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
      unbind();
   }
}
