
#include <phui/SDLBridge.h>
#include "LoginState.h"


namespace client {

   LoginState::LoginState() {
      /// @todo make this the same size as the game window?  depends
      /// if we want the UI to be resolution-dependent or not...
      mRoot = phui::CreateRoot(640, 480);

      const int border_w = 50;
      const int border_h = 50;

      // main window
      phui::Window* window = new phui::Window();
      window->setPosition(border_w, border_h);
      window->setSize(640 - border_w * 2, 480 - border_h * 2);
      window->setBackgroundColor(phui::Colorf(0.2, 0.3, 0.8, 0.8));
      window->show();

      mRoot->add(window);

      mUsername = addLabeledField(window, "Username", 1);
      mPassword = addLabeledField(window, "Password", 2);
      mServer   = addLabeledField(window, "Server",   3);
      mPort     = addLabeledField(window, "Port",     4);

      mUsername->setText("aegis");
      mPassword->setText(":)");
      mServer->setText("localhost");
      mPort->setText("35791");

      phui::Button* connect = new phui::Button("Connect");
      connect->setPosition(50, 300);
      connect->setSize(100, 20);
      window->add(connect);

      phui::Button* quit = new phui::Button("Quit");
      quit->setPosition(200, 300);
      quit->setSize(100, 20);
      window->add(quit);

      phui::CheckBox* spectator = new phui::CheckBox();
      spectator->setPosition(50, 250);
      spectator->setSize(20, 20);
      spectator->show();

      phui::Label* spectatorLbl = new phui::Label("Login as Spectator");
      spectatorLbl->setPosition(80, 250);
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

   phui::TextField*
   LoginState::addLabeledField(phui::WidgetContainer* container,
                               const std::string& label,
                               int index)
   {
      phui::Label* labelWidget = new phui::Label(label.c_str());
      labelWidget->setPosition(50, 50 * index);
      labelWidget->setSize(100, 20);
      labelWidget->setBackgroundColor(phui::Colorf(0, 0, 0, 0.1f));
      container->add(labelWidget);

      phui::TextField* textWidget = new phui::TextField;
      textWidget->setPosition(200, 50 * index);
      textWidget->setSize(150, 20);
      container->add(textWidget);
      return textWidget;
   }

}
