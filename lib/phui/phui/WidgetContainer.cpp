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
 * Date modified: $Date: 2002-04-22 05:07:20 $
 * Version:       $Revision: 1.13 $
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
      mCapturedWidget = 0;
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
      for (size_t i = 0; i < mWidgets.size(); ++i) {
         if (mWidgets[i] == widget) {
            mWidgets.erase(mWidgets.begin() + i);
            widget->mParent = 0;
         }
      }
   }

   void WidgetContainer::draw() {
      // draw all children to this widget
      // draw them backwards so it's from the back to the front, visually
      for (int i = int(mWidgets.size()) - 1; i >= 0; --i) {
         Widget* wgt = mWidgets[i];
         Point pos = wgt->getPosition();

         // only draw if the widget is visible
         if (wgt->isVisible()) {
            ::glTranslatef(pos.x, pos.y, 0);
            wgt->draw();
            ::glTranslatef(-pos.x, -pos.y, 0);
         }
      }      
   }

   void WidgetContainer::onKeyDown(InputKey key) {
      if (Widget* focus = getFocus()) {
         focus->onKeyDown(key);
      }
   }

   void WidgetContainer::onKeyUp(InputKey key) {
      if (Widget* focus = getFocus()) {
         focus->onKeyUp(key);
      }
   }

   void WidgetContainer::onMouseDown(InputButton button, const Point& p) {

      // mouse down always releases widget capture
      capture(0);

      if (Widget* widget = getWidgetAt(p)) {
         focus(widget);
         capture(widget);
         widget->onMouseDown(button, p - widget->getPosition());
      }
   }

   void WidgetContainer::onMouseUp(InputButton button, const Point& p) {
      if (Widget* widget = getMouseWidget(p)) {
         widget->onMouseUp(button, p - widget->getPosition());
         capture(0);
      }
   }

   void WidgetContainer::onMouseMove(const Point& p) {
      if (Widget* widget = getMouseWidget(p)) {
         widget->onMouseMove(p - widget->getPosition());
      }
   }

   void WidgetContainer::focus(Widget* widget) {
      for (size_t i = 0; i < mWidgets.size(); ++i) {
         if (mWidgets[i] == widget) {
            std::swap(mWidgets[0], mWidgets[i]);
            break;
         }
      }
   }

   Widget* WidgetContainer::getFocus() {
      return (mWidgets.empty() ? 0 : mWidgets[0]);
   }

   void WidgetContainer::capture(Widget* widget) {
      mCapturedWidget = widget;
   }

   Widget* WidgetContainer::getCapture() {
      return mCapturedWidget;
   }

   Widget* WidgetContainer::getWidgetAt(const Point& p) {
      for (size_t i = 0; i < mWidgets.size(); ++i) {
         if (mWidgets[i]->contains(p)) {
            return mWidgets[i];
         }
      }
      return 0;
   }

   Widget* WidgetContainer::getMouseWidget(const Point& p) {
      Widget* widget = getCapture();
      return (widget ? widget : getWidgetAt(p));
   }


} // namespace phui
