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
 * File:          $RCSfile: CheckBox.cpp,v $
 * Date modified: $Date: 2005-01-23 21:46:47 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "CheckBox.h"

namespace phui
{
   CheckBox::CheckBox(bool checked)
   {
      mIsChecked = checked;
   }

   CheckBoxPtr CheckBox::create()
   {
      CheckBoxPtr obj(new CheckBox());
      return obj;
   }

   CheckBoxPtr CheckBox::create(bool checked)
   {
      CheckBoxPtr obj(new CheckBox(checked));
      return obj;
   }

   void CheckBox::draw()
   {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
      {
         glVertex2i(0,     0     );
         glVertex2i(width, 0     );
         glVertex2i(width, height);
         glVertex2i(0,     height);
      }
      glEnd();

      if (isChecked())
      {
         glColor(getForegroundColor());
         glBegin(GL_LINES);
         {
            glVertex2i(0,     0);
            glVertex2i(width, height);
            glVertex2i(width, 0);
            glVertex2i(0,     height);
         }
         glEnd();
      }

   }

   void CheckBox::check()
   {
      setChecked(true);
   }

   void CheckBox::uncheck()
   {
      setChecked(false);
   }

   void CheckBox::setChecked(bool checked)
   {
      mIsChecked = checked;
   }

   bool CheckBox::isChecked() const
   {
      return mIsChecked;
   }

   void CheckBox::onMouseDown(InputButton button, const Point& p)
   {
      if (button == BUTTON_LEFT)
      {
         setChecked(!isChecked());
      }
   }
}
