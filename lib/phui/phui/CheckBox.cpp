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
 * File:          $RCSfile: CheckBox.cpp,v $
 * Date modified: $Date: 2002-04-28 15:51:59 $
 * Version:       $Revision: 1.3 $
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
#include "CheckBox.h"


namespace phui {

   CheckBox::CheckBox(bool checked) {
      mIsChecked = checked;      
   }

   void CheckBox::draw() {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
      glVertex2i(0,     0     );
      glVertex2i(width, 0     );
      glVertex2i(width, height);
      glVertex2i(0,     height);
      glEnd();

      if (isChecked()) {
         glColor(getForegroundColor());
         glBegin(GL_LINES);
         glVertex2i(0,     0);
         glVertex2i(width, height);
         glVertex2i(width, 0);
         glVertex2i(0,     height);
         glEnd();
      }
      
   }

   void CheckBox::check() {
      mIsChecked = true;
   }

   void CheckBox::uncheck() {
      mIsChecked = false;
   }

   bool CheckBox::isChecked() {
      return mIsChecked;
   }

   void CheckBox::onMouseDown(InputButton button, const Point& p) {
      if (button == BUTTON_LEFT) {
         mIsChecked = !isChecked();
      }
   }

}
