#ifndef CLIENT_LOGIN_STATE_H
#define CLIENT_LOGIN_STATE_H


#include <phui/phui.h>
#include <phui/ActionListener.h>
#include "State.h"
#include "Scene.h"


namespace client {

   class LoginState : public State, public phui::ActionListener {
   public:
      LoginState();
      ~LoginState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      virtual void onAction(const phui::ActionEvent& evt);
   private:
      phui::TextField* addLabeledField(phui::WidgetContainer* container,
                                       const std::string& label,
                                       int index);

      phui::RootWidget* mRoot;
      phui::TextField*  mUsername;
      phui::TextField*  mPassword;
      phui::TextField*  mServer;
      phui::TextField*  mPort;
      phui::Button* mConnect;
      phui::Button* mQuit;

      Scene mScene;
   };

}


#endif
