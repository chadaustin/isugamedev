/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: RootWidget.cpp,v $
 * Date modified: $Date: 2002-04-22 04:34:36 $
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
#include "RootWidget.h"

namespace phui {

   RootWidget::RootWidget( int width, int height ) {
      setSize(width, height);
   }

   RootWidget::~RootWidget() {
   }

   void RootWidget::draw() {
      int width, height;
      getSize(width, height);

      // setup the projection matrix
      glMatrixMode( GL_PROJECTION );
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D( 0, width, height, 0 );

      // setup the modelview matrix
      glMatrixMode( GL_MODELVIEW );
      glPushMatrix();
      glLoadIdentity();

      // disable depth testing since all draws occur at the same level
      glDisable( GL_DEPTH_TEST );

      // draw children
      WidgetContainer::draw();

      // re-enable depth testing
      glEnable( GL_DEPTH_TEST );

      glMatrixMode(GL_MODELVIEW);
      glPopMatrix(); // modelview

      glMatrixMode(GL_PROJECTION);
      glPopMatrix(); // projection
   }

} // namespace phui
