/**
 * Public domain.
 * Original Author: Chad Austin <aegis@aegisknight.org>
 *
 * Hacked a bit by Ben Scott <nonchocoboy@sourceforge.net>
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

/**
 * Encapsulates the "fun" of OpenGL texturing so that you can just create a
 * Texture object from an image file and start using it in your OpenGL
 * application.
 */
class Texture
{
public:
   /**
    * Creates a new texture from the given image file.
    *
    * @param filename      the image file to create the texture from
    */
   Texture(const char* filename);

   /**
    * Destroys this texture and releases the image memory.
    */
   ~Texture();

   /**
    * Sets this texture as the current OpenGL texture. Subsequent OpenGL
    * rendering commands will apply this texture to the rendered objects.
    */
   void bind();

private:
   /**
    * The OpenGL texture "name". This basically stores the unique ID managed by
    * OpenGL for this texture.
    */
   GLuint mTexture;
};

#endif
