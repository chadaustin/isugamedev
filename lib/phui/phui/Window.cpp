/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Window.cpp,v $
 * Date modified: $Date: 2002-02-24 08:52:12 $
 * Version:       $Revision: 1.6 $
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
#include "Window.h"
#include <GL/gl.h>

namespace phui {

   Window::Window() {
      mVisible = false;
   }

   Window::~Window() {
   }

   void Window::draw() {
      // render the background
      glColor( mBackgroundColor );
      glBegin(GL_TRIANGLE_FAN);
         glVertex2i( mX,          mY           );
         glVertex2i( mX + mWidth, mY           );
         glVertex2i( mX + mWidth, mY + mHeight );
         glVertex2i( mX,          mY + mHeight );
      glEnd();

      // draw the children on top of us
      drawChildren();
   }

} // namespace phui
