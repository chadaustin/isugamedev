#ifndef MW_ENDING_STATE_H
#define MW_ENDING_STATE_H

#include "State.h"
#include "Texture.h"

namespace mw
{
   class Application;

   class EndingState : public State
   {
   public:
      EndingState(Application*);
      ~EndingState();

      void update(float dt);
      void draw();
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);

   private:
      void startTransition();

      Texture* mImage;
      float mElapsedTime;  // seconds
      bool mLeavingState;
   };
}

#endif
