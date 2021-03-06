#ifndef MW_HUD_H
#define MW_HUD_H


#include <gltext.h>
#include <GL/gl.h>
#include <GL/glu.h>

   class HUD
   {
   public:
      HUD();
      ~HUD();

      void draw(float x, float y, float width, float height);

   private:
      gltext::FontPtr mFont;
      gltext::FontRendererPtr mFontRenderer;
   };

#endif
