/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: WidgetContainer.cpp,v $
 * Date modified: $Date: 2002-04-15 09:29:58 $
 * Version:       $Revision: 1.10 $
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
#include <algorithm>
#include <functional>
#include "WidgetContainer.h"
#include <GL/gl.h>

namespace phui {

   WidgetContainer::WidgetContainer() {
   }

   WidgetContainer::~WidgetContainer() {
   }

   void WidgetContainer::add(Widget* widget) {
      if (widget->getParent()) {
         widget->getParent()->remove(widget);
      }
      mWidgets.push_back(widget);
      widget->mParent = this;
   }

   void WidgetContainer::remove(Widget* widget) {
      mWidgets.remove(widget);
      widget->mParent = NULL;
   }

   void WidgetContainer::draw() {
      // draw all children to this widget
      drawChildren();
   }

   void WidgetContainer::drawChildren() {
      // draw all children to this widget
      std::list<Widget*>::iterator itr;
      for (itr = mWidgets.begin(); itr != mWidgets.end(); ++itr) {
         Widget* wgt = *itr;

         // only draw if the widget is visible
         if (wgt->isVisible()) {
            ::glTranslatef( mX, mY, 0 );
            wgt->draw();
            ::glTranslatef( -mX, -mY, 0 );
         }
      }
   }

} // namespace phui
