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
 * File:          $RCSfile: Button.cpp,v $
 * Date modified: $Date: 2002-04-28 15:51:59 $
 * Version:       $Revision: 1.18 $
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
#include "Button.h"
#include <GL/gl.h>
#include "FontRendererCache.h"
#include "WidgetContainer.h"
#include <algorithm>

namespace phui {

   Button::Button()
      : mText("")
      , mButtonDown(false)
   {
   }

   Button::Button(const std::string& text)
      : mText(text)
      , mButtonDown(false)
   {
   }

   Button::~Button() {
   }

   void Button::draw() {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      // draw the button background
      glColor(mButtonDown ? getForegroundColor() : getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
         glVertex2i(0,     0     );
         glVertex2i(width, 0     );
         glVertex2i(width, height);
         glVertex2i(0,     height);
      glEnd();
      
      // draw text
      glColor(mButtonDown ? getBackgroundColor() : getForegroundColor());

      FontRenderer* renderer = FontRendererCache::getFontRenderer(getFont());
      
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

      renderer->draw(mText, fontX, fontY);
      
      if (hasFocus()) {
         glBegin(GL_LINE_LOOP);
         glVertex2i(0,     0     );
         glVertex2i(width, 0     );
         glVertex2i(width, height);
         glVertex2i(0,     height);
         glEnd();
      }
   }

   void Button::setText(const std::string& text) {
      mText = text;
   }

   const std::string& Button::getText() const {
      return mText;
   }

   void Button::onMouseDown(InputButton button, const Point& p) {
      std::cout << "Button::onMouseDown " << p << std::endl;
      /// @todo capture the mouse so we can receive the MouseUp event even if
      //        the mouse is no longer inside the button.
      if (button == BUTTON_LEFT) {
         std::cout<<"\tLMB"<<std::endl;
         mButtonDown = true;
      }
   }

   void Button::onMouseUp(InputButton button, const Point& p) {
      std::cout << "Button::onMouseUp " << p << std::endl;
      if (button == BUTTON_LEFT) {
         std::cout<<"\tLMB"<<std::endl;
         mButtonDown = false;

         // Only fire button pressed event if the mouse was released
         // inside this button.
         if (contains(p)) {
            std::cout<<"FIRE button pressed"<<std::endl;
            fireActionEvent();
         }
      }
   }

   void Button::addActionListener(ActionListener* listener) {
      mListeners.push_back(listener);
   }

   void Button::removeActionListener(ActionListener* listener) {
      ListenerIter itr;
      itr = std::find(mListeners.begin(), mListeners.end(), listener);
      if (itr != mListeners.end()) {
         mListeners.erase(itr);
      }
   }

   void Button::fireActionEvent() {
      ActionEvent evt(this);

      for(ListenerIter itr=mListeners.begin(); itr!=mListeners.end(); itr++) {
         (*itr)->onAction(evt);
      }
   }

} // namespace phui
