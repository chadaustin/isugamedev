#ifndef MW_HUD_H
#define MW_HUD_H


#include <gltext.h>
#include "Player.h"


namespace mw
{

   class HUD
   {
   public:
      HUD();
      ~HUD();

      void draw(float width, float height, Player& player, float fps);

   private:
      gltext::Font* mFont;
      gltext::FontRenderer* mFontRenderer;
      void drawTape(float width, float height, float maxValue, float currentValue,bool horizontal);

   };
}

#endif
