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
 * Date modified: $Date: 2002-02-24 08:48:18 $
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
#ifndef PHUI_WIDGET_CONTAINER_H
#define PHUI_WIDGET_CONTAINER_H

#include "phuiCommon.h"
#include <list>
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
       * Draws this widget and all of its children.
       */
      void draw();

   protected:
      /**
       * Draws each widget in this container widget. WidgetContainer
       * implementations will want to call this if they reimplement draw() to
       * draw the child components correctly.
       */
      virtual void drawChildren();

   private:
      std::list<Widget*> mWidgets;
  };

} // namespace phui

#endif
