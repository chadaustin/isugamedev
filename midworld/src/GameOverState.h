#ifndef MW_GAME_OVER_STATE_H
#define MW_GAME_OVER_STATE_H


#include "State.h"
#include "Texture.h"


namespace mw
{
   class Application;

   class GameOverState : public State
   {
   public:
      GameOverState(Application*);
      ~GameOverState();

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
