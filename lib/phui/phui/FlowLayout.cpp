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
 * File:          $RCSfile: FlowLayout.cpp,v $
 * Date modified: $Date: 2003-01-05 02:19:16 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "FlowLayout.h"
#include "Widget.h"

namespace phui
{
   void
   FlowLayout::add(const Point& point, const Size& size)
   {
      Point newPos = point;
      int newWidth = size.getWidth();
      int newHeight = size.getHeight();
      int containerHeight = mContainer->getSize().getHeight();
      int containerWidth = mContainer->getSize().getWidth();
      if (mConstraint->getType() == "FLOW_VERTICAL")
      {
         //Figure out if we're moving to the right or down
         if (mCurrentHeight == containerHeight)
         {
            //Check to see if the object is too wide
            if (size.getWidth() > containerWidth - mCurrentMaxWidth)
            {
               newWidth = containerWidth - mCurrentMaxWidth;
            }
            //Check to see if the object is too tall
            if (size.getHeight() > containerHeight)
            {
               newHeight = containerHeight;
            }
            //Move the object to the right
            newPos.x = mCurrentMaxWidth;
            newPos.y = 0;
            mCurrentWidth = mCurrentMaxWidth;
            mCurrentMaxWidth += newWidth;
         }
         else
         {
            //Check to see if the object is too wide
            if (size.getWidth() > containerWidth - mCurrentWidth)
            {
               newWidth = containerWidth - mCurrentWidth;
            }
            //Check to see if the object is too tall
            if (size.getHeight() > containerHeight - mCurrentHeight)
            {
               newHeight = containerHeight - mCurrentHeight;
            }
            //Move the object down
            newPos.x = mCurrentWidth;
            if (newWidth > mCurrentMaxWidth - mCurrentWidth)
            {
               mCurrentMaxWidth = mCurrentWidth + newWidth;
            }
            newPos.y = mCurrentHeight;
            mCurrentHeight += newHeight;
         }
      }
      else
      {
         //Figure out where we're moving
         if (mCurrentWidth == containerWidth)
         {
            //Check to see if the object is too tall
            if (size.getHeight() > containerHeight - mCurrentMaxHeight)
            {
               newHeight = containerHeight - mCurrentMaxHeight;
            }
            //Check to see if the object is too wide
            if (size.getWidth() > containerWidth)
            {
               newWidth = containerWidth;
            }
            mCurrentWidth = 0;
            newPos.x = 0;
            newPos.y = mCurrentMaxHeight;
            mCurrentHeight = mCurrentMaxHeight;
            mCurrentMaxHeight += newHeight;
         }
         else
         {
            //Check to see if the object is too tall
            if (size.getHeight() > containerHeight - mCurrentHeight)
            {
               newHeight = containerHeight - mCurrentHeight;
            }
            //Check to see if the object is too wide
            if (size.getWidth() > containerWidth - mCurrentWidth)
            {
               newWidth = containerWidth - mCurrentWidth;
            }
            //Move the object to the right
            newPos.x = mCurrentWidth;
            mCurrentWidth += newWidth;
            newPos.y = mCurrentHeight;
            if (newHeight > mCurrentMaxHeight - mCurrentHeight)
            {
               mCurrentMaxHeight = newHeight;
            }
         }
      }
      //Set the widget
      WidgetPtr widget = mContainer->getWidgetAt(point);
      widget->setPosition(newPos);
      widget->setSize( Size(newWidth, newHeight) );
   }
}
