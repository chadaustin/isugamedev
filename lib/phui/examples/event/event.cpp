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
 * Date modified: $Date: 2002-04-15 19:59:13 $
 * Version:       $Revision: 1.3 $
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


namespace {
   phui::RootWidget* gRoot;
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

phui::InputKey GlutToPhuiKey(char key) {
   printf("%d\n", (int)key);

   return phui::KEY_UNKNOWN;
/*
   // check major ranges
   if (key >= '0' && key <= '9') {
      return KEY_0 + key - '0';
   } else if ((key >= 'a' && key <= 'z') ||
              (key >= 'A' && key <= 'Z')) {
      return KEY_A + tolower(key) - 'a';
   }


   switch (key) {
      case 8:   return phui::KEY_TAB;
      case 9:   return phui::KEY_BACKSPACE;
      case 27:  return phui::KEY_ESCAPE;
      case 127: return phui::KEY_DELETE;
         
      default:  return phui::KEY_UNKNOWN;
   }
*/
}

phui::InputKey GlutSpecialToPhuiKey(int key) {
   printf("%d\n", (int)key);

#define KEY(name) \
   case GLUT_KEY_##name: return phui::KEY_##name

   switch (key) {
      KEY(F1);
      KEY(F2);
      KEY(F3);
      KEY(F4);
      KEY(F5);
      KEY(F6);
      KEY(F7);
      KEY(F8);
      KEY(F9);
      KEY(F10);
      KEY(F11);
      KEY(F12);
      KEY(LEFT);
      KEY(UP);
      KEY(RIGHT);
      KEY(DOWN);
      KEY(PAGE_UP);
      KEY(PAGE_DOWN);
      KEY(HOME);
      KEY(END);
      KEY(INSERT);
      default: return phui::KEY_UNKNOWN;
   }

#undef KEY

}

phui::InputButton GlutToPhuiButton(int button) {
   if (button == GLUT_LEFT_BUTTON) {
      return phui::BUTTON_LEFT;
   } else if (button == GLUT_MIDDLE_BUTTON) {
      return phui::BUTTON_MIDDLE;
   } else if (button == GLUT_RIGHT_BUTTON) {
      return phui::BUTTON_RIGHT;
   } else {
      return phui::BUTTON_UNKNOWN;
   }
}

void OnKeyboardDown(unsigned char key, int /*x*/, int /*y*/) {
   gRoot->onKeyDown(GlutToPhuiKey(key));
}

void OnKeyboardUp(unsigned char key, int /*x*/, int /*y*/) {
   gRoot->onKeyUp(GlutToPhuiKey(key));
}

void OnSpecialDown(int key, int /*x*/, int /*y*/) {
   gRoot->onKeyDown(GlutSpecialToPhuiKey(key));
}

void OnSpecialUp(int key, int /*x*/, int /*y*/) {
   gRoot->onKeyUp(GlutSpecialToPhuiKey(key));
}

void OnMouseClick(int button, int state, int /*x*/, int /*y*/) {
   if (state == GLUT_DOWN) {
      gRoot->onMouseDown(GlutToPhuiButton(button));
   } else {
      gRoot->onMouseUp(GlutToPhuiButton(button));
   }
}

void OnMouseMove(int x, int y) {
   gRoot->onMouseMove(x, y);
}

int main(int argc, char** argv) {
   try {
      glutInitWindowSize(640, 480);
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

      glutCreateWindow("Event Example");

      glutDisplayFunc(display);
      glutReshapeFunc(reshape);

      // register input callbacks
      glutKeyboardFunc(OnKeyboardDown);
      glutKeyboardUpFunc(OnKeyboardUp);
      glutSpecialFunc(OnSpecialDown);
      glutSpecialUpFunc(OnSpecialUp);
      glutMouseFunc(OnMouseClick);
      glutMotionFunc(OnMouseMove);
      glutPassiveMotionFunc(OnMouseMove);

      gRoot = phui::CreateRoot(
         glutGet(GLUT_WINDOW_WIDTH),
         glutGet(GLUT_WINDOW_HEIGHT));
      phui::Window* window(new phui::Window());
      window->setPosition(150, 75);
      window->setSize(300, 250);
      window->setVisible(true);
      window->setBackgroundColor(phui::Colorf(1, 0, 0, 0.5f));

      gRoot->add(window);

      glutMainLoop();
   }
   catch (std::exception& e) {
      std::cerr << "caught exception: " << e.what() << std::endl;
   }
}
