#ifndef CLIENT_LOGIN_STATE_H
#define CLIENT_LOGIN_STATE_H


#include <phui/phui.h>
#include "State.h"


namespace client {

   class LoginState : public State {
   public:
      LoginState();
      ~LoginState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

   private:
      phui::RootWidget* mRoot;
   };

}


#endif
