/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_TEXTURE_H
#define MW_TEXTURE_H


#include <string>
#include <SDL/SDL_opengl.h>


namespace mw
{

   class Texture
   {
   public:
      Texture(const std::string& filename);
      ~Texture();

      void bind();
      void drawRectangle(int x1, int y1, int x2, int y2);

   private:
      GLuint mTexture;
      float mRealWidth;
      float mRealHeight;
   };

}


#endif
