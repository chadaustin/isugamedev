/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Button.cpp,v $
 * Date modified: $Date: 2002-04-22 11:55:17 $
 * Version:       $Revision: 1.12 $
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
#include "Button.h"
#include <GL/gl.h>
#include "FontRenderer.h"
#include "WidgetContainer.h"

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
      int width, height;
      getSize(width, height);

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

      renderer.draw(mText, fontX, fontY);
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
            /// @todo fire ButtonPressed event
         }
      }
   }

} // namespace phui
