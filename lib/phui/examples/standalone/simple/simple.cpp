/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: simple.cpp,v $
 * Date modified: $Date: 2005-01-25 23:11:40 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <gltext/FTFont.h>
#include <gltext/gltext.h>
#include <phui/phui.h>
#include <phui/DriverManager.h>
#include <iostream>

int main(int argc, char* argv)
{
   std::cout << "Phui built with the " 
             << phui::DriverManager::Instance().getSupportedDrivers()
             << " drivers." 
             << std::endl;
   gltext::FontPtr font = gltext::FTFont::create("arial.ttf", 12, 32);
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
