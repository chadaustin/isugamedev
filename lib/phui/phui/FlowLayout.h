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
 * File:          $RCSfile: FlowLayout.h,v $
 * Date modified: $Date: 2005-01-25 17:28:50 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_FLOW_LAYOUT_H
#define PHUI_FLOW_LAYOUT_H

#include "LayoutConstraint.h"
#include "LayoutManager.h"
#include "Point.h"
#include "Size.h"
#include "WidgetContainer.h"

namespace phui
{
   class FlowLayout : public LayoutManager
   {
   public:
      /**
       * Constructor
       *
       * @param   container   the widget container to manage
       * @param   constraint  the layout contstraint to follow
       */
      FlowLayout(WidgetContainer* container, LayoutConstraintPtr constraint)
         : LayoutManager(container, constraint)
         , mCurrentWidth(0)
         , mCurrentMaxWidth(0)
         , mCurrentHeight(0)
         , mCurrentMaxHeight(0)
      {}

      /**
       * Adds a widget's specifications to this layout manager
       *
       * @param   point       the point where the widget will be added
       * @param   size        the size of the widget to be added
       */
      virtual void add(const Point& point, const Size& size);

      /**
       * Removes a widget's specifications from this layout manager
       *
       * @param   point       the point of the widget to be removed
       */
      virtual void remove(const Point& point)
      {
         //TODO: Resize
         LayoutManager::remove(point);
      }

   private:
      ///Current Width
      int mCurrentWidth;

      ///Current Maximum Width
      int mCurrentMaxWidth;

      ///Current Height
      int mCurrentHeight;

      ///Current Maximum Height
      int mCurrentMaxHeight;
   };
}

#endif
