#ifndef CLIENT_GARAGE_STATE_H
#define CLIENT_GARAGE_STATE_H


#include <phui/phui.h>
#include "State.h"
#include "Scene.h"


namespace client {

   class GarageState : public State {
   public:
      GarageState();
      ~GarageState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);
   };

}


#endif
