/**
 * Public domain.
 * Original Author: Chad Austin <aegis@aegisknight.org>
 *
 * Hacked a bit by Ben Scott <nonchocoboy@sourceforge.net>
 */
#include <memory>
#include <iostream>
#include <corona.h>
#include "Texture.h"
using namespace std;
using namespace corona;


Texture::Texture(const char* filename)
{
   cout<<"Creating texture: "<<filename<<" ... "<<flush;

   // Load the image using Corona. We use auto_ptr to make sure that the Image
   // object is deleted automagically once we've given OpenGL the texture data
   // and thus no longer need it ourselves.
   auto_ptr<Image> image(OpenImage(filename, FF_AUTODETECT, PF_R8G8B8A8));

   // Check if OpenImage failed by testing to see if the pointer to the corona
   // Image held by our auto_ptr is NULL.
   if (! image.get())
   {
      // Set the texture name to 0 so that the call to glDeleteTextures in the
      // destructor will not cause funky shit to happen. glDeleteTextures
      // ignores texture names with the value 0.
      mTexture = 0;
      std::cerr<<"failed!"<<std::endl;
      return;
   }

   // Get a unique texture name for our new texture.
   glGenTextures(1, &mTexture);

   // Tell OpenGL that this is going to be a 2D image and sets it as the
   // current texture for future drawing.
   glBindTexture(GL_TEXTURE_2D, mTexture);

   // Generate a 2D texture in 32-bit RGBA format from our image and store it in
   // the current texture we specified in the last glBindTexture() call.
   glTexImage2D(
         GL_TEXTURE_2D,       // The target texture type always use GL_TEXTURE_2D
         0,                   // Texture level, used for LOD textures.
         GL_RGBA8,            // Data format to use internally to GL.
         image->getWidth(),   // Image width (must be a power of 2)
         image->getHeight(),  // Image height (must be a power of 2)
         0,                   // Border size, usually you want 0
         GL_RGBA,             // Data format for the incoming image data
         GL_UNSIGNED_BYTE,    // Type of each color in a pixel being passed in.
         image->getPixels()   // Our 1D array of image pixels
   );

   // Tell OpenGL to Clamp the texture so that any texture coordinates greater
   // than 1 will be mapped to 1. This way, you know you can generate your
   // texels in the range of 0.0 to 1.0.
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   // Tell OpenGL to use a linear average of the nearby pixels to compute the
   // pixel color for each texel. This setting is generally fast with decent
   // image quality.
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   std::cout<<"successful"<<std::endl;
}


Texture::~Texture()
{
   // Make sure we tell OpenGL to release the texture memory we created. If the
   // texture name is 0 - as in we had an error in the constructor.
   glDeleteTextures(1, &mTexture);
}


void Texture::bind()
{
   // Make this texture the current texture to be used for subsequent OpenGL
   // rendering commands.
   glBindTexture(GL_TEXTURE_2D, mTexture);
}
