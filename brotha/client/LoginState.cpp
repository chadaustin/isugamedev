
#include <phui/SDLBridge.h>
#include "LoginState.h"


namespace client {

   LoginState::LoginState() {
      /// @todo make this the same size as the game window?  depends
      /// if we want the UI to be resolution-dependent or not...
      mRoot = phui::CreateRoot(640, 480);

      phui::Window* window = new phui::Window();
      window->setPosition(100, 100);
      window->setSize(300, 200);
      window->setBackgroundColor(phui::Colorf(0.2, 0.3, 0.8, 0.8));
      window->show();

      phui::Button* connect = new phui::Button("Connect");
      connect->setPosition(200, 100);
      connect->setSize(50, 20);
      connect->show();

      phui::CheckBox* spectator = new phui::CheckBox();
      spectator->setPosition(80, 120);
      spectator->setSize(20, 20);
      spectator->show();

      phui::Label* spectatorLbl = new phui::Label("Login as Spectator");
      spectatorLbl->setPosition(110, 120);
      spectatorLbl->setSize(150,20);
      spectatorLbl->show();

      window->add(connect);
      window->add(spectator);
      window->add(spectatorLbl);

      mRoot->add(window);
   }

   LoginState::~LoginState() {
   }

   void
   LoginState::draw() {
      glClear(GL_COLOR_BUFFER_BIT);
      mRoot->draw();
   }

   void
   LoginState::update(BrothaApp* app, int elapsedTime) {
      // don't do anything  ^__^
   }

   void
   LoginState::onKeyPress(SDLKey sym, bool down) {
      if (down) {
         mRoot->onKeyDown(phui::SDLToPhuiKey(sym));
      } else {
         mRoot->onKeyUp(phui::SDLToPhuiKey(sym));
      }
   }

   void
   LoginState::onMousePress(Uint8 button, bool down, int x, int y) {
      phui::Point p(x, y);
      if (down) {
         mRoot->onMouseDown(phui::SDLToPhuiButton(button), p);
      } else {
         mRoot->onMouseUp(phui::SDLToPhuiButton(button), p);
      }
   }

   void
   LoginState::onMouseMove(int x, int y) {
      mRoot->onMouseMove(phui::Point(x, y));
   }

}
