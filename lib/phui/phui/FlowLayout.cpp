/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

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
      Widget* widget = mContainer->getWidgetAt(point);
      widget->setPosition(newPos);
      widget->setSize( Size(newWidth, newHeight) );
   }

}
