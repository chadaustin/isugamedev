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
 * File:          $RCSfile: LayoutManager.h,v $
 * Date modified: $Date: 2003-01-04 02:47:57 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_LAYOUT_MANAGER_H
#define PHUI_LAYOUT_MANAGER_H

#include <utility>
#include <vector>
#include "LayoutConstraint.h"
#include "Size.h"
#include "Point.h"

namespace phui
{
   class WidgetContainer;
   
   /**
    * Represents a Layout Manager for graphical components.  A Layout Manager
    * will automatically resize and move widgets to meet the constraints of the
    * layout.
    */
   class LayoutManager
   {
   public:
      
      /**
       * Constructor
       *
       * @param   container   the widget container to manage
       * @param   constraint  the layout constraint to follow
       */
      LayoutManager(WidgetContainer *container, LayoutConstraint* constraint)
         : mConstraint(constraint), mContainer(container) 
      {
      }
     
      virtual ~LayoutManager()
      {
         delete mConstraint;
      }

      /**
       * Adds a widget's specifications to this layout manager
       *
       * @param   point       the point where the widget will be added
       * @param   size        the size of the widget to be added
       */
      virtual void add(const Point& point, const Size& size)
      {
         mWidgets.push_back( std::make_pair(point, size) );
      }
      
      /**
       * Removes a widget's specifications from this layout manager
       *
       * @param   point       the point of the widget to be removed
       */
      virtual void remove(const Point& point);

      /**
       * Checks to see if the current set of widgets is valid within the
       * constraints of this manager
       *
       * @return     true if the set of widgets is valid, false otherwise
       */
      virtual bool isValid() const
      {
         return true;
      }

      /**
       * Resizes a set of widgets to make it valid within the constraints of
       * this layout manager
       */
      virtual void resize()
      {
         return;
      }
      
   protected:
      ///The layout constraint to follow
      LayoutConstraint* mConstraint;
      ///The container being managed by this layout manager
      WidgetContainer* mContainer;
      ///The points and sizes of all widgets that are in this layout manager
      std::vector<std::pair< Point, Size > > mWidgets;
   private:
      
   };
}

#endif
