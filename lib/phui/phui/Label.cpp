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
 * File:          $RCSfile: Label.cpp,v $
 * Date modified: $Date: 2005-01-25 17:28:50 $
 * Version:       $Revision: 1.15 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>
#include "Label.h"
#include "WidgetContainer.h"

namespace phui
{
   Label::Label()
   {}

   Label::Label(const std::string& text)
      : mText(text)
   {
      setBackgroundColor(NONE);
   }

   LabelPtr Label::create()
   {
      LabelPtr obj(new Label());
      return obj;
   }

   LabelPtr Label::create(const std::string& text)
   {
      LabelPtr obj(new Label(text));
      return obj;
   }

   void Label::draw()
   {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();
      gltext::FontPtr font = getFont();

      // draw the label background
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

      gltext::FontRendererPtr renderer = gltext::CreateRenderer(gltext::PIXMAP,
                                                                font);

      double labelWidth = double(renderer->getWidth(mText.c_str()));
      double fontHeight = double(font->getAscent() + font->getDescent());

      //Lets store the Matrix so we don't piss anyone off
      glPushMatrix();

      //These checks see if the button Label fits inside the
      //button.  If not start in the lower left-hand corner of
      //the button and render the text.
      double yLoc = (height - fontHeight)/2.0;
      if (yLoc < 0)
      {
         yLoc = 0;
      }

      double xLoc = (width - labelWidth)/2.0;
      if (xLoc < 0)
      {
         xLoc = 0;
      }
      glTranslatef(GLfloat(xLoc), GLfloat(height - yLoc), 0.0f);

      renderer->render(mText.c_str());

      //Lets restore the Matrix
      glPopMatrix();
   }

   void Label::setText(const std::string& text)
   {
      mText = text;
   }

   const std::string& Label::getText() const
   {
      return mText;
   }
}
