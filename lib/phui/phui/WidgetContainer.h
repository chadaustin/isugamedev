/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: WidgetContainer.h,v $
 * Date modified: $Date: 2002-04-22 04:55:28 $
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
#ifndef PHUI_WIDGET_CONTAINER_H
#define PHUI_WIDGET_CONTAINER_H

#include "phuiCommon.h"
#include <vector>
#include <iostream>
#include "Widget.h"

namespace phui {

   /**
    * Abstract widget specialization. This is the base class for all widgets
    * implementations that may contain other widgets within them.
    */
   class WidgetContainer : public Widget {
   protected:
      /**
       * This class is abstract. You create a derived instance instead.
       */
      WidgetContainer();
      ~WidgetContainer();

   public:
      /**
       * Adds the given widget to this container widget.
       *
       * @param widget     the widget to add
       */
      void add(Widget* widget);

      /**
       * Removes the given widget from this container widget.
       * Doesn't destroy widget, just removes from container.
       *
       * @param widget     the widget to remove
       */
      void remove(Widget* widget);

      /**
       * Draws this widget and all of its children.
       */
      void draw();

      void onKeyDown(InputKey key);
      void onKeyUp(InputKey key);
      void onMouseDown(InputButton button, const Point& p);
      void onMouseUp(InputButton button, const Point& p);
      void onMouseMove(const Point& p);

      void focus(Widget* widget);
      Widget* getFocus();

      void capture(Widget* widget);
      Widget* getCapture();

      Widget* getWidgetAt(const Point& p);

      // this name sucks ass
      Widget* getMouseWidget(const Point& p);

   private:
      std::vector<Widget*> mWidgets;  // sorted from topmost to bottommost
                                      // topmost has focus

      Widget* mCapturedWidget;
   };

} // namespace phui

#endif
