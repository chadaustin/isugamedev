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
 * File:          $RCSfile: RootWidget.cpp,v $
 * Date modified: $Date: 2005-01-25 17:28:51 $
 * Version:       $Revision: 1.18 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "RootWidget.h"

namespace phui
{
   RootWidget::RootWidget(int width, int height)
   {
      setSize(phui::Size(width, height));
   }

   RootWidget::~RootWidget()
   {}

   void RootWidget::draw()
   {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      // setup the projection matrix
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);

      // setup the modelview matrix
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      // Make sure the client isn't affected by our changes to OpenGL state.
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                   GL_ENABLE_BIT | GL_SCISSOR_BIT);
      {
         // disable depth testing since all draws occur at the same level
         glDisable(GL_DEPTH_TEST);

         // we need to clip widgets
         glEnable(GL_SCISSOR_TEST);

         // turn on alpha blending
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

         drawChildren();
         drawPointer();
      }
      glPopAttrib();

      // restore old matrices
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
   }

   void RootWidget::onMouseMove(const Point& p)
   {
      mPointerPosition = p;
   }

   void RootWidget::drawPointer()
   {
      glColor(WHITE);
      glBegin(GL_LINES);
      glVertex(mPointerPosition);
      glVertex(mPointerPosition + Point(5, 5));
      glEnd();
   }

   void RootWidget::drawChildren()
   {
      WidgetContainer::draw();
   }
}
