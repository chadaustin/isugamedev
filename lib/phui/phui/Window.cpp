/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Window.cpp,v $
 * Date modified: $Date: 2002-04-28 18:55:09 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Josh Carlson, Ben Scott
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
#include "Window.h"
#include <GL/gl.h>

namespace phui {

   Window::Window()
      : mTitle("")
   {
      setVisible(false);
   }

   Window::Window(const std::string& title)
      : mTitle(title)
   {
      // XXXaegis - why is this different from Window() ?  Shouldn't
      // they be the same?
      setVisible(true);
   }

   Window::~Window() {
   }

   void Window::draw() {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      // render the background
      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
      glVertex2i(0,     0);
      glVertex2i(width, 0);
      glVertex2i(width, height);
      glVertex2i(0,     height);
      glEnd();

      if (hasFocus()) {
         glColor(getForegroundColor());
         glBegin(GL_LINE_LOOP);
         glVertex2i(0,     0);
         glVertex2i(width, 0);
         glVertex2i(width, height);
         glVertex2i(0,     height);
         glEnd();
      }

      WidgetContainer::draw();
   }

   void Window::addWindowListener(WindowListener* listener) {
      mListeners.push_back(listener);
   }

   void Window::removeWindowListener(WindowListener* listener) {
      ListenerIter itr;
      itr = std::find(mListeners.begin(), mListeners.end(), listener);
      if (itr != mListeners.end()) {
         mListeners.erase(itr);
      }
   }

} // namespace phui
