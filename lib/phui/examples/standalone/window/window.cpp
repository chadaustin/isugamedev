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
 * File:          $RCSfile: window.cpp,v $
 * Date modified: $Date: 2005-01-23 21:49:01 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <GL/glut.h>
#include <phui/phui.h>
#include <phui/DriverManager.h>
#include <phui/GLUTDriver.h>
#include <phui/SDLDriver.h>

static phui::RootWidgetPtr gUI;
static phui::WindowPtr gWnd;

int main(int argc, char** argv)
{
   try
   {
      // Select our driver
//      phui::DriverManager::Instance().setDriver(phui::GLUTDriver::ID);
      phui::DriverManager::Instance().setDriver("SDL");
      // Create our root widget
      gUI = phui::CreateRoot(640, 480);

      // Register it with the GLUT driver
      phui::DriverManager::Instance().registerRoot(gUI);

      gWnd = phui::Window::create("my contacts blow");
      gWnd->setPosition(phui::Point(150, 75));
      gWnd->setSize(phui::Size(300, 250));
      gWnd->show();
      gWnd->setBackgroundColor(phui::Colorf(1, 0, 0, 0.75f));

      phui::WindowPtr window(phui::Window::create("other window"));
      window->setPosition(phui::Point(250, 175));
      window->setSize(phui::Size(300, 250));
      window->show();
      window->setBackgroundColor(phui::Colorf(0, 0, 1, 0.75f));

      phui::ButtonPtr btn(phui::Button::create(
                            "This is a really long string Push me!"));
      btn->setPosition(phui::Point(10, 10));
      btn->setSize(phui::Size(75, 30));
      btn->show();
      btn->setBackgroundColor(phui::Colorf(0,0,1,0.7));
      gWnd->add(btn);

      phui::LabelPtr lbl(phui::Label::create("Label me!"));
      lbl->setPosition(phui::Point(75, 10));
      lbl->setSize(phui::Size(100, 45));
      lbl->show();
      lbl->setBackgroundColor(phui::Colorf(0,1,1,0.7));
      gWnd->add(lbl);

      gUI->add(gWnd);
      gUI->add(window);

      phui::DriverManager::Instance().start();
   }
   catch (std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
   }
}
