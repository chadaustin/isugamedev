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
 * File:          $RCSfile: TextField.cpp,v $
 * Date modified: $Date: 2005-01-23 21:46:48 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>
#include "TextField.h"
#include "WidgetContainer.h"

namespace phui
{
   TextField::TextField()
      : mText(""), mCursorScreenPosition(0), mCursorCharacterPosition(0)
   {}

   TextField::TextField(const std::string& text)
      : mText(text), mCursorScreenPosition(0), mCursorCharacterPosition(0)
   {}

   TextField::~TextField()
   {}

   TextFieldPtr TextField::create()
   {
      TextFieldPtr obj(new TextField());
      return obj;
   }

   TextFieldPtr TextField::create(const std::string& text)
   {
      TextFieldPtr obj(new TextField(text));
      return obj;
   }

   void TextField::draw()
   {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      // draw the button background
      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
      {
         glVertex2i(0,     0     );
         glVertex2i(width, 0     );
         glVertex2i(width, height);
         glVertex2i(0,     height);
      }
      glEnd();

      // draw text
      glColor(getForegroundColor());

 /*     FontRenderer* renderer = FontRendererCache::getFontRenderer(getFont());

      const Insets& i = getInsets();
//      int w = width  - i.getLeft() - i.getRight();
//      int h = height - i.getTop()  - i.getBottom();
      unsigned int fontHeight = renderer->getHeight();
//      unsigned int fontWidth = renderer.getWidth(mText);
      unsigned int fontAscent = fontHeight - renderer->getDescent();

      int textRectX = i.getLeft();
      int textRectY = i.getTop();
//      int textRectW = width  - (i.getRight()  + textRectX);
//      int textRectH = height - (i.getBottom() + textRectY);

      int fontX = textRectX;
      int fontY = textRectY + fontAscent;

      if(hasFocus()) {
         std::string cursor = "|";
         renderer->draw(cursor, fontX+mCursorScreenPosition, fontY);
      }
      renderer->draw(mText, fontX, fontY);*/
   }

   void TextField::setText(const std::string& text)
   {
/*      FontRenderer* renderer = FontRendererCache::getFontRenderer(getFont());
      mCursorScreenPosition=renderer->getWidth(text);
      mCursorCharacterPosition=text.length();

      mText = text;*/
   }

   const std::string& TextField::getText() const
   {
      return mText;
   }

   void TextField::onKeyDown(InputKey key)
   {
/*      FontRenderer* renderer = FontRendererCache::getFontRenderer(getFont());
      std::string toAdd; // if we are to add anything, put it here
      if(key == KEY_RIGHT) {
         if(mCursorCharacterPosition < mText.length()) {
            mCursorScreenPosition+=renderer->getWidth(mText.substr(mCursorCharacterPosition,1));
            mCursorCharacterPosition++;
         }
      } else if(key == KEY_LEFT) {
         if(mCursorCharacterPosition > 0) {
            mCursorCharacterPosition--;
            mCursorScreenPosition-=renderer->getWidth(mText.substr(mCursorCharacterPosition,1));
         }
      } else if(key == KEY_BACKSPACE) {
         if(mCursorCharacterPosition > 0) {
            mCursorCharacterPosition--;
            mCursorScreenPosition-=renderer->getWidth(mText.substr(mCursorCharacterPosition,1));
            mText.erase(mCursorCharacterPosition,1);
         }
      } else if(key == KEY_DELETE) {
         if(mCursorCharacterPosition < mText.length()) {
            mText.erase(mCursorCharacterPosition,1);
         }
      } else if(key == KEY_SPACE) {
         toAdd+=' ';
      } else if(key >= KEY_A && key <= KEY_Z) {
         toAdd+=(char)(key-KEY_A)+'a';
      } else if(key >= KEY_0 && key <= KEY_9) {
         toAdd+=(char)(key-KEY_0)+'0';
      } else if(key == KEY_PERIOD) {
         toAdd+='.';
      }

      if(!toAdd.empty()) {
         mText.insert(mCursorCharacterPosition, toAdd);
         mCursorScreenPosition+=renderer->getWidth(toAdd);
         mCursorCharacterPosition++;
      }*/
   }
}
