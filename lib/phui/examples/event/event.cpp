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
 * File:          $RCSfile: event.cpp,v $
 * Date modified: $Date: 2003-01-05 02:19:15 $
 * Version:       $Revision: 1.23 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <stdio.h>
#include <GL/glut.h>
#include <phui/phui.h>
#include <phui/GLUTBridge.h>


namespace
{
   phui::RootWidgetPtr gRoot;
   int gContext; /// GLUT context
}

class WidgetHider : public phui::ActionListener
{
public:
   WidgetHider(phui::WidgetPtr wgt)
      : mWidget(wgt)
   {}

   ~WidgetHider()
   {}

   void onAction(const phui::ActionEvent& evt)
   {
      mWidget->setVisible(! mWidget->isVisible());
   }

private:
   phui::WidgetPtr mWidget;
};

class WndListener : public phui::WindowListener
{
public:
   ~WndListener()
   {}

   void onWindowOpened(const phui::WindowEvent& evt)
   {
      std::cout<<"Opened a window"<<std::endl;
   }

   void onWindowClosed(const phui::WindowEvent& evt)
   {
      std::cout<<"Closed a window"<<std::endl;
   }

   void onWindowFocused(const phui::WindowEvent& evt) {}
   void onWindowUnfocused(const phui::WindowEvent& evt) {}
};

void idle()
{
   if (glutGetWindow() != gContext)
   {
      glutSetWindow(gContext);
   }
   glutPostRedisplay();
}

void display()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   gRoot->draw();
   glutSwapBuffers();
}

void reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   gRoot->setSize(width, height);
}

int main(int argc, char** argv)
{
   try
   {
      glutInitWindowSize(640, 480);
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

      gContext = glutCreateWindow("Event Example");

      glutIdleFunc(idle);
      glutDisplayFunc(display);
      glutReshapeFunc(reshape);

      glutSetCursor(GLUT_CURSOR_NONE);

      // create our root widget
      gRoot = phui::CreateRoot(
         glutGet(GLUT_WINDOW_WIDTH),
         glutGet(GLUT_WINDOW_HEIGHT));

      // register it with glut
      phui::glutRegisterRoot(gRoot);

      phui::WindowPtr window(phui::Window::create());
      window->setPosition(150, 75);
      window->setSize(300, 250);
      window->show();
      window->setBackgroundColor(phui::Colorf(1, 0, 0, 0.75f));

      phui::WindowPtr wnd(phui::Window::create());
      wnd->setPosition(250, 175);
      wnd->setSize(300, 250);
      wnd->show();
      wnd->setBackgroundColor(phui::Colorf(0, 0, 1, 0.75f));
      phui::WindowListenerPtr wnd_listener(new WndListener());
      wnd->addWindowListener(wnd_listener);

      phui::WindowPtr w(phui::Window::create());
      w->setPosition(100, 100);
      w->setSize(50, 50);
      w->show();
      w->setBackgroundColor(phui::Colorf(0, 1, 0, 0.75f));
      wnd->add(w);

      phui::CheckBoxPtr cb(phui::CheckBox::create());
      cb->setPosition(220, 40);
      cb->setSize(20, 20);
      cb->show();
      cb->setBackgroundColor(phui::Colorf(0, 0, 0, 0.2f));
      cb->setForegroundColor(phui::Colorf(1, 0, 1, 1));
      window->add(cb);

      phui::ButtonPtr button(phui::Button::create("Icky very very very icky"));
      button->setPosition(20, 20);
      button->setSize(100,50);
      button->show();
      button->setBackgroundColor(phui::Colorf(0,0,1,0.5f));
      phui::ActionListenerPtr action_listener(new WidgetHider(wnd));
      button->addActionListener(action_listener);
      window->add(button);

      phui::TextFieldPtr txt(phui::TextField::create());
      txt->setPosition(20,100);
      txt->setSize(100,50);
      txt->show();
      txt->setBackgroundColor(phui::Colorf(1,1,1,1.0f));
      txt->setForegroundColor(phui::Colorf(0,0,0,1.0f));
      window->add(txt);

      phui::ListBoxPtr lst(phui::ListBox::create());
      lst->setPosition(130,100);
      lst->setSize(100,100);
      lst->show();
      lst->setBackgroundColor(phui::Colorf(1,1,1,1.0f));
      lst->setForegroundColor(phui::Colorf(0,0,0,1.0f));
      lst->add("Apples");
      lst->add("Oranges");
      lst->add("Bananas");
      lst->add("Pears");
      lst->add("Peaches");
      window->add(lst);

      gRoot->add(window);
      gRoot->add(wnd);

      glutMainLoop();
   }
   catch (std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
   }
}
