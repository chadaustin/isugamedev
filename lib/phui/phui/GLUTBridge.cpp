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
 * File:          $RCSfile: GLUTBridge.cpp,v $
 * Date modified: $Date: 2003-01-04 06:44:08 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <GL/glut.h>
#include "GLUTBridge.h"
#include "RootWidget.h"

namespace phui {

   /// set by glutRegisterRoot
   RootWidget* gRoot;


   /// @todo finish this off
   InputKey GlutToPhuiKey(char key) {
      if(key >= 'a' && key <= 'z') {
         return (InputKey)(KEY_A + (key - 'a'));
      } else if(key >= '0' && key <= '9') {
         return (InputKey)(KEY_0 + (key - '0'));
      }

      switch (key) {
         case 8:   return KEY_BACKSPACE;
         case 9:   return KEY_TAB;
         case 27:  return KEY_ESCAPE;
         case 32:  return KEY_SPACE;
         case 127: return KEY_DELETE;

         default:  return KEY_UNKNOWN;
      }
   }


   /// @todo finish this off
   InputKey GlutSpecialToPhuiKey(int key) {

#define KEY(name) \
   case GLUT_KEY_##name: return KEY_##name

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
         default: return KEY_UNKNOWN;
      }

#undef KEY

   }


   InputButton GlutToPhuiButton(int button) {
      switch (button) {
         case GLUT_LEFT_BUTTON:   return BUTTON_LEFT;
         case GLUT_MIDDLE_BUTTON: return BUTTON_MIDDLE;
         case GLUT_RIGHT_BUTTON:  return BUTTON_RIGHT;
         default:                 return BUTTON_UNKNOWN;
      }
   }

   namespace {

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

      void OnMouseClick(int button, int state, int x, int y) {
         InputButton phui_button = GlutToPhuiButton(button);
         if (state == GLUT_DOWN) {
            gRoot->onMouseDown(phui_button, Point(x, y));
         } else {
            gRoot->onMouseUp(phui_button, Point(x, y));
         }
      }

      void OnMouseMove(int x, int y) {
         gRoot->onMouseMove(Point(x, y));
      }

   }

   void glutRegisterRoot(RootWidget* root) {
      gRoot = root;

      glutKeyboardFunc(OnKeyboardDown);
      glutKeyboardUpFunc(OnKeyboardUp);
      glutSpecialFunc(OnSpecialDown);
      glutSpecialUpFunc(OnSpecialUp);
      glutMouseFunc(OnMouseClick);
      glutMotionFunc(OnMouseMove);
      glutPassiveMotionFunc(OnMouseMove);
   }
}
