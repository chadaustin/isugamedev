#ifndef MW_STORY_STATE_H
#define MW_STORY_STATE_H


#include <gltext.h>
#include "State.h"
#include "Texture.h"


namespace mw
{
   class StoryState : public State
   {
   public:
      StoryState(Application*);
      ~StoryState();

      void update(float dt);
      void draw();
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);

   private:
      float mElapsedTime;

      Texture* mStoryImage;
      gltext::Font* mFont;
      gltext::FontRenderer* mFontRenderer;
   };
}


#endif
