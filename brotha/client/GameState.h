#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H


#include <phui/phui.h>
#include "State.h"
#include "Scene.h"


namespace client {

   class GameState : public State {
   public:
      GameState();
      ~GameState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);
   };

}


#endif
