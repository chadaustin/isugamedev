/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Widget.cpp,v $
 * Date modified: $Date: 2002-04-17 07:40:02 $
 * Version:       $Revision: 1.4 $
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
#include "Widget.h"
#include "WidgetContainer.h"

namespace phui
{

   Widget::Widget()
      : mX(0), mY(0), mWidth(0), mHeight(0), mInsetX(0), mInsetY(0),
        mEnabled(true), mVisible(true), mBackgroundColor(0,0,0,0),
        mForegroundColor(1,1,1,1), mFont("arial", Font::PLAIN, 12),
        mParent(NULL)
   {}

   Widget::~Widget()
   {}

   void Widget::getPosition(int& x, int& y) const
   {
      x = mX;
      y = mY;
   }

   void Widget::setPosition(int x, int y)
   {
      mX = x;
      mY = y;
   }
   void Widget::getSize(int& width, int& height) const
   {
      width = mWidth;
      height = mHeight;
   }

   void Widget::setSize(int width, int height)
   {
      mWidth = width;
      mHeight = height;
   }

   void Widget::getInsets(int insetX, int insetY)
   {
      insetX = mInsetX;
      insetY = mInsetY;
   }

   void Widget::setInsets(int insetX, int insetY)
   {
      mInsetX = insetX;
      mInsetY = insetY;
   }

   bool Widget::isEnabled() const
   {
      return mEnabled;
   }

   void Widget::setEnabled( bool enabled )
   {
      mEnabled = enabled;
   }

   bool Widget::isVisible() const
   {
      return mVisible;
   }

   void Widget::setVisible( bool visible )
   {
      mVisible = visible;
   }

   void Widget::setBackgroundColor( const Colorf& clr )
   {
      mBackgroundColor = clr;
   }

   const Colorf& Widget::getBackgroundColor() const
   {
      return mBackgroundColor;
   }

   void Widget::setForegroundColor( const Colorf& clr )
   {
      mForegroundColor = clr;
   }

   const Colorf& Widget::getForegroundColor() const
   {
      return mForegroundColor;
   }

   void Widget::setFont( const Font& font )
   {
      mFont = font;
   }

   const Font& Widget::getFont() const
   {
      return mFont;
   }

   const WidgetContainer* Widget::getParent() const
   {
      return mParent;
   }

   WidgetContainer* Widget::getParent()
   {
      return mParent;
   }

   bool Widget::contains(int x, int y) const
   {
      return ((x >= 0) && (y >= 0) && (x < mWidth) && (y < mHeight))
   }

   void Widget::getScreenPosition(int& x, int& y) const
   {
      const WidgetContainer* parent = getParent();
      getPosition(x, y);
      while (parent)
      {
         int px, py;
         parent->getPosition(px, py);
         x += px;
         y += py;
         parent = parent->getParent();
      }
   }
}
