/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TextField.cpp,v $
 * Date modified: $Date: 2002-04-22 06:19:36 $
 * Version:       $Revision: 1.2 $
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
#include "TextField.h"
#include <GL/gl.h>
#include "FontRenderer.h"
#include "WidgetContainer.h"

namespace phui {

   TextField::TextField()
      : mText(""), mCursorScreenPosition(0), mCursorCharacterPosition(0)
   {}

   TextField::TextField(const std::string& text)
      : mText(text), mCursorScreenPosition(0), mCursorCharacterPosition(0)
   {}

   TextField::~TextField()
   {
   }

   void TextField::draw()
   {
      int width, height;
      getSize(width, height);

      // draw the button background
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

      std::string cursor = "|";
      renderer.draw(cursor, fontX+mCursorScreenPosition, fontY);
      renderer.draw(mText, fontX, fontY);
   }

   void TextField::setText(const std::string& text)
   {
      mText = text;
   }

   const std::string& TextField::getText() const
   {
      return mText;
   }

   void TextField::onKeyDown(InputKey key)
   {
      FontRenderer renderer(getFont());

      if(key == KEY_RIGHT) {
         if(mCursorCharacterPosition < mText.length()) {
            mCursorScreenPosition+=renderer.getWidth(mText.substr(mCursorCharacterPosition,1));
            mCursorCharacterPosition++;
         }
      } else if(key == KEY_LEFT) {
         if(mCursorCharacterPosition > 0) {
            mCursorCharacterPosition--;
            mCursorScreenPosition-=renderer.getWidth(mText.substr(mCursorCharacterPosition,1));
         }
      } else if(key == KEY_BACKSPACE) {
         if(mCursorCharacterPosition > 0) {
            mCursorCharacterPosition--;
            mCursorScreenPosition-=renderer.getWidth(mText.substr(mCursorCharacterPosition,1));
            mText.erase(mCursorCharacterPosition,1);
         }
      } else if(key == KEY_DELETE) {
         if(mCursorCharacterPosition < mText.length()) {
            mText.erase(mCursorCharacterPosition,1);
         }
      } else if(key >= KEY_A && key <= KEY_Z) {
         std::string toAdd;
         toAdd+=(char)(key-KEY_A)+'a';

         mText.insert(mCursorCharacterPosition, toAdd);

         mCursorScreenPosition+=renderer.getWidth(toAdd);
         mCursorCharacterPosition++;
      }
   }

} // namespace phui
