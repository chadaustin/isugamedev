#ifndef CLIENT_STATE_H
#define CLIENT_STATE_H


#include <SDL/SDL.h>


namespace client {

   class BrothaApp;

   class State {
   public:
      virtual ~State() { }
      virtual void draw() = 0;
      virtual void update(BrothaApp* app, int elapsedTime) = 0;

      virtual void onKeyPress(SDLKey sym, bool down) = 0;
      virtual void onMousePress(Uint8 button, bool down, int x, int y) = 0;
      virtual void onMouseMove(int x, int y) = 0;
   };

}

#endif
