#ifndef MW_HUD_H
#define MW_HUD_H


#include <gltext.h>


namespace mw
{
   class GameState;

   class HUD
   {
   public:
      HUD();
      ~HUD();

      void draw(GameState& gs);

   private:
      gltext::Font* mFont;
      gltext::FontRenderer* mFontRenderer;
   };

}

#endif
