/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ListBox.cpp,v $
 * Date modified: $Date: 2002-04-22 07:22:39 $
 * Version:       $Revision: 1.1 $
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
#include "ListBox.h"
#include <GL/gl.h>
#include "FontRenderer.h"
#include "WidgetContainer.h"

namespace phui {

   ListBox::ListBox()
      : mSelectedItem(-1)
   {
   }

   ListBox::~ListBox() {
   }

   void ListBox::draw() {
      int width, height;
      getSize(width, height);

      // draw the box background
      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
         glVertex2i(0,     0     );
         glVertex2i(width, 0     );
         glVertex2i(width, height);
         glVertex2i(0,     height);
      glEnd();

      // draw text
      glColor(getForegroundColor());

      FontRenderer renderer(getFont());

      const Insets& i = getInsets();
//      int w = width  - i.getLeft() - i.getRight();
//      int h = height - i.getTop()  - i.getBottom();
      unsigned int fontHeight = renderer.getHeight();
//      unsigned int fontWidth = renderer.getWidth(mText);
      unsigned int fontAscent = fontHeight - renderer.getDescent();

      int textRectX = i.getLeft();
      int textRectY = i.getTop();
//      int textRectW = width  - (i.getRight()  + textRectX);
//      int textRectH = height - (i.getBottom() + textRectY);

      int fontX = textRectX;
      int fontY = textRectY + fontAscent;

      for(unsigned int x=0;x<mItems.size();++x) {
         if(mSelectedItem == x) {
            // draw the selected box
            glColor(getForegroundColor());
            glBegin(GL_TRIANGLE_FAN);
               glVertex2i(0,     fontHeight*x);
               glVertex2i(width, fontHeight*x);
               glVertex2i(width, fontHeight*(x+1));
               glVertex2i(0,     fontHeight*(x+1));
            glEnd();
            glColor(getBackgroundColor());
         }
         renderer.draw(mItems[x], fontX, fontY+(x*fontHeight));
         if(mSelectedItem == x) {
            glColor(getForegroundColor());
         }
      }
   }

   void ListBox::add(const std::string& text) {
      mItems.push_back(text);
   }

   void ListBox::onMouseDown(InputButton button, const Point& p) {
      if (button == BUTTON_LEFT) {
         FontRenderer renderer(getFont());
         mSelectedItem = (p.y-(p.y%renderer.getHeight()))/renderer.getHeight();
      }
   }
} // namespace phui
