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
 * File:          $RCSfile: WidgetContainer.cpp,v $
 * Date modified: $Date: 2003-01-04 06:44:08 $
 * Version:       $Revision: 1.27 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <algorithm>
#include <functional>

#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>
#include "EmptyConstraint.h"
#include "WidgetContainer.h"

namespace phui
{
   WidgetContainer::WidgetContainer()
      : mCapturedWidget(0)
   {
      mLayoutManager = new LayoutManager(this, new EmptyConstraint() );
   }

   WidgetContainer::WidgetContainer(LayoutManager* manager)
      : mLayoutManager(manager), mCapturedWidget(0)
   {}

   WidgetContainer::~WidgetContainer()
   {}

   void WidgetContainer::add(Widget* widget) {
      if (widget->getParent()) {
         widget->getParent()->remove(widget);
      }
      mWidgets.push_back(widget);
      widget->mParent = this;
      mLayoutManager->add(widget->getPosition(), widget->getSize());
   }

   void WidgetContainer::remove(Widget* widget) {
      for (size_t i = 0; i < mWidgets.size(); ++i) {
         if (mWidgets[i] == widget) {
            mWidgets.erase(mWidgets.begin() + i);
            widget->mParent = 0;
            mLayoutManager->remove(widget->getPosition());
         }
      }
   }

   void WidgetContainer::draw()
   {
      // Check to see if the current setup is valid
      if (!mLayoutManager->isValid())
      {
         mLayoutManager->resize();
      }
      // draw all children to this widget
      // draw them backwards so it's from the back to the front, visually
      for (int i = int(mWidgets.size()) - 1; i >= 0; --i) {
         Widget* wgt = mWidgets[i];
         Point pos = wgt->getPosition();

         // only draw if the widget is visible
         if (wgt->isVisible()) {

            glTranslatef((float)pos.x, (float)pos.y, 0);
            wgt->draw();
            glTranslatef((float)-pos.x, (float)-pos.y, 0);

         }
      }
   }

   void WidgetContainer::setLayoutManager(LayoutManager* manager)
   {
      mLayoutManager = manager;
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
         // we'll want to simply ignore this event if widget is disabled
         if(widget->isEnabled()) {
            focus(widget);
            capture(widget);
            widget->onMouseDown(button, p - widget->getPosition());
         }
      }
   }

   void WidgetContainer::onMouseUp(InputButton button, const Point& p) {
      if (Widget* widget = getMouseWidget(p)) {
         // we'll want to simply ignore this event if widget is disabled
         if(widget->isEnabled()) {
            widget->onMouseUp(button, p - widget->getPosition());
            capture(0);
         }
      }
   }

   void WidgetContainer::onMouseMove(const Point& p) {
      if (Widget* widget = getMouseWidget(p)) {
         // we'll want to simply ignore this event if widget is disabled
         if(widget->isEnabled()) {
            widget->onMouseMove(p - widget->getPosition());
         }
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
         Widget* wgt = mWidgets[i];

         // Make sure the widget is visible
         if (wgt->isVisible()) {
            // Check if this widget contains the given point
            if (wgt->contains(p - wgt->getPosition())) {
               return mWidgets[i];
            }
         }
      }
      return 0;
   }

   Widget* WidgetContainer::getMouseWidget(const Point& p) {
      Widget* widget = getCapture();
      return (widget ? widget : getWidgetAt(p));
   }
}
