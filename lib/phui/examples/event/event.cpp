/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: event.cpp,v $
 * Date modified: $Date: 2002-04-26 10:27:35 $
 * Version:       $Revision: 1.18 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Ben Scott
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
 ************************************************************** phui-cpr-end */

#include <stdio.h>
#include <GL/glut.h>
#include <phui/phui.h>
#include <phui/GLUTBridge.h>


namespace {
   phui::RootWidget* gRoot;
   int gContext; /// GLUT context
}

class BtnListener : public phui::ActionListener
{
public:
   BtnListener(phui::Window* wnd)
      : mWnd(wnd)
   {}

   virtual ~BtnListener() {}

   virtual void onAction(const phui::ActionEvent& evt)
   {
      mWnd->setVisible(false);
   }

private:
   phui::Window* mWnd;
};

void idle() {
   if (glutGetWindow() != gContext) {
      glutSetWindow(gContext);
   }
   glutPostRedisplay();
}

void display() {
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT);
   gRoot->draw();
   glutSwapBuffers();
}

void reshape(int width, int height) {
   glViewport(0, 0, width, height);
   gRoot->setSize(width, height);
}

void OnKeyboardDown(unsigned char key, int /*x*/, int /*y*/) {
   gRoot->onKeyDown(phui::GlutToPhuiKey(key));
}

void OnKeyboardUp(unsigned char key, int /*x*/, int /*y*/) {
   gRoot->onKeyUp(phui::GlutToPhuiKey(key));
}

void OnSpecialDown(int key, int /*x*/, int /*y*/) {
   gRoot->onKeyDown(phui::GlutSpecialToPhuiKey(key));
}

void OnSpecialUp(int key, int /*x*/, int /*y*/) {
   gRoot->onKeyUp(phui::GlutSpecialToPhuiKey(key));
}

void OnMouseClick(int button, int state, int x, int y) {
   phui::InputButton phui_button = phui::GlutToPhuiButton(button);
   if (state == GLUT_DOWN) {
      gRoot->onMouseDown(phui_button, phui::Point(x, y));
   } else {
      gRoot->onMouseUp(phui_button, phui::Point(x, y));
   }
}

void OnMouseMove(int x, int y) {
   gRoot->onMouseMove(phui::Point(x, y));
}

int main(int argc, char** argv) {
   try {
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

      phui::Window* window(new phui::Window());
      window->setPosition(150, 75);
      window->setSize(300, 250);
      window->show();
      window->setBackgroundColor(phui::Colorf(1, 0, 0, 0.75f));

      phui::Window* wnd(new phui::Window());
      wnd->setPosition(250, 175);
      wnd->setSize(300, 250);
      wnd->show();
      wnd->setBackgroundColor(phui::Colorf(0, 0, 1, 0.75f));

      phui::Window* w(new phui::Window());
      w->setPosition(100, 100);
      w->setSize(50, 50);
      w->show();
      w->setBackgroundColor(phui::Colorf(0, 1, 0, 0.75f));
      wnd->add(w);

      phui::Button* button(new phui::Button("Icky very very very icky"));
      button->setPosition(20, 20);
      button->setSize(100,50);
      button->show();
      button->setBackgroundColor(phui::Colorf(0,0,1,0.5f));
      window->add(button);
      BtnListener* btnLstr(new BtnListener(window));
      button->addActionListener(btnLstr);

      phui::TextField* txt(new phui::TextField());
      txt->setPosition(20,100);
      txt->setSize(100,50);
      txt->show();
      txt->setBackgroundColor(phui::Colorf(1,1,1,1.0f));
      txt->setForegroundColor(phui::Colorf(0,0,0,1.0f));
      window->add(txt);

      phui::ListBox* lst(new phui::ListBox());
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

      phui::CheckBox* cb(new phui::CheckBox());
      cb->setPosition(220, 40);
      cb->setSize(20, 20);
      cb->show();
      cb->setBackgroundColor(phui::Colorf(0, 0, 0, 0.2f));
      cb->setForegroundColor(phui::Colorf(1, 0, 1, 1));
      window->add(cb);

      gRoot->add(window);
      gRoot->add(wnd);

      glutMainLoop();
   }
   catch (std::exception& e) {
      std::cerr << "caught exception: " << e.what() << std::endl;
   }
}
