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
 * Date modified: $Date: 2002-04-17 07:25:26 $
 * Version:       $Revision: 1.7 $
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
      : mText(""), mButtonDown(false)
   {}

   Button::Button(const std::string& text)
      : mText(text), mButtonDown(false)
   {}

   Button::~Button()
   {
   }

   void Button::draw()
   {
      glPushMatrix();
      glTranslatef((GLfloat)mX, (GLfloat)mY, 0.0f);
      // draw the button background
      if (mButtonDown)
      {
         glColor(mForegroundColor);
      }
      else
      {
         glColor(mBackgroundColor);
      }
      glBegin(GL_TRIANGLE_FAN);
         glVertex2i(0,      0      );
         glVertex2i(mWidth, 0      );
         glVertex2i(mWidth, mHeight);
         glVertex2i(0,      mHeight);
      glEnd();

      // draw text
      if (mButtonDown)
      {
         glColor(mBackgroundColor);
      }
      else
      {
         glColor(mForegroundColor);
      }
      FontRenderer renderer(mFont);

      int w = mWidth - (2*mInsetX);
      int h = mHeight - (2*mInsetY);
      unsigned int fontHeight = renderer.getHeight();
      unsigned int fontWidth = renderer.getWidth(mText);
      unsigned int fontAscent = fontHeight - renderer.getDescent();

      int textRectX = mInsetX + (w/2) - (fontWidth/2);
      int textRectY = mInsetY + (h/2) - (fontHeight/2);
      int textRectW = w;
      int textRectH = h;

      int fontX = textRectX;
      int fontY = textRectY + fontAscent;

      renderer.draw(mText, fontX, fontY);

      glPopMatrix();
   }

   void Button::setText(const std::string& text)
   {
      mText = text;
   }

   const std::string& Button::getText() const
   {
      return mText;
   }

   void Button::onMouseDown(InputButton button, int x, int y)
   {
      std::cout<<"Button::onMouseDown("<<x<<", "<<y<<")"<<std::endl;
      /// @todo capture the mouse so we can receive the MouseUp event even if
      //        the mouse is no longer inside the button.
      if (button == BUTTON_LEFT)
      {
         std::cout<<"\tLMB"<<std::endl;
         mButtonDown = true;
      }
   }

   void Button::onMouseUp(InputButton button, int x, int y)
   {
      std::cout<<"Button::onMouseUp("<<x<<", "<<y<<")"<<std::endl;
      if (button == BUTTON_LEFT)
      {
         std::cout<<"\tLMB"<<std::endl;
         mButtonDown = false;

         // Only fire button pressed event if the mouse was released inside
         // this button.
         if (contains(x, y))
         {
            std::cout<<"FIRE button pressed"<<std::endl;
            /// @todo fire ButtonPressed event
         }
      }
   }
} // namespace phui
