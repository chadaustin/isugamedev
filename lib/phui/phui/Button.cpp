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
 * Date modified: $Date: 2002-04-17 05:38:57 $
 * Version:       $Revision: 1.5 $
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
      : mLabel("")
   {}

   Button::Button( const std::string& label )
      : mLabel( label )
   {}

   Button::~Button() {
   }

   void Button::draw()
   {
      glPushMatrix();
      glTranslatef((GLfloat)mX, (GLfloat)mY, 0.0f);
      // draw the button background
      glColor( mBackgroundColor );
      glBegin(GL_TRIANGLE_FAN);
         glVertex2i(0,      0       );
         glVertex2i(mWidth, 0       );
         glVertex2i(mWidth, mHeight );
         glVertex2i(0,      mHeight );
      glEnd();

      // draw label text
      glColor( mForegroundColor );
      FontRenderer renderer( mFont );

      int w = mWidth - (2*mInsetX);
      int h = mHeight - (2*mInsetY);
      unsigned int fontHeight = renderer.getHeight();
      unsigned int fontWidth = renderer.getWidth(mLabel);
      unsigned int fontAscent = fontHeight - renderer.getDescent();

      int textRectX = mInsetX + (w/2) - (fontWidth/2);
      int textRectY = mInsetY + (h/2) - (fontHeight/2);
      int textRectW = w;
      int textRectH = h;

      int fontX = textRectX;
      int fontY = textRectY + fontAscent;

      renderer.draw( mLabel, fontX, fontY );

      glPopMatrix();
   }

   void Button::setLabel( const std::string& label )
   {
      mLabel = label;
   }

   const std::string& Button::getLabel() const
   {
      return mLabel;
   }

} // namespace phui
