#include <phui/phui.h>
#include <phui/DriverManager.h>
#include <iostream>

int main(int argc, char* argv)
{
   std::cout << "Phui built with the " 
             << phui::DriverManager::Instance().getSupportedDrivers()
             << " drivers." 
             << std::endl;
   phui::RootWidgetPtr root = new phui::RootWidget(640, 480);
   phui::WindowPtr window = phui::Window::create();
   phui::ButtonPtr btn = phui::Button::create("Push Me");
   btn->setPosition(phui::Point(10, 10));
   btn->setSize(phui::Size(50, 50));
   btn->show();
   window->setBackgroundColor(phui::Colorf(1.0, 0.0, 0.0, 0.0));
   window->setPosition(phui::Point(150, 75));
   window->setSize(phui::Size(300, 300));
   window->add(btn);
   window->show();
   root->add(window);
   phui::DriverManager::Instance().setDriver("SDL");
   phui::DriverManager::Instance().registerRoot(root);
   phui::DriverManager::Instance().start();
   
   return 0;
}
