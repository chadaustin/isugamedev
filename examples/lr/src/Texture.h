#ifndef LR_TEXTURE_H
#define LR_TEXTURE_H

#include <string>
#include <SDL_opengl.h>

namespace lr
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

}

#endif
