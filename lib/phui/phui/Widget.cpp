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
 * File:          $RCSfile: Widget.cpp,v $
 * Date modified: $Date: 2003-01-05 14:10:05 $
 * Version:       $Revision: 1.23 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <stdio.h>
#include <stdexcept>
#include "Widget.h"
#include "WidgetContainer.h"

namespace phui
{
   Widget::Widget()
      : mSize(0,0)
      , mEnabled(true)
      , mVisible(true)
      , mBackgroundColor(BLACK)
      , mForegroundColor(WHITE)
   {
      mFont = gltext::CreateFont("arial.ttf", gltext::PLAIN, 12);
      if (!mFont)
      {
         throw std::runtime_error("Font not found");
      }
   }

   Widget::~Widget()
   {}

   void Widget::draw()
   {}

   const Point& Widget::getPosition() const
   {
      return mPosition;
   }

   void Widget::setPosition(const Point& p)
   {
      mPosition = p;
   }

   const Size& Widget::getSize() const
   {
      return mSize;
   }

   void Widget::setSize(const Size& size)
   {
      mSize = size;
   }

   const Insets& Widget::getInsets() const
   {
      return mInsets;
   }

   void Widget::setInsets(const Insets& insets)
   {
      mInsets = insets;
   }

   bool Widget::isEnabled() const
   {
      return mEnabled;
   }

   void Widget::setEnabled(bool enabled)
   {
      mEnabled = enabled;
   }

   bool Widget::isVisible() const
   {
      return mVisible;
   }

   void Widget::setVisible(bool visible)
   {
      mVisible = visible;
   }

   void Widget::setBackgroundColor(const Colorf& clr)
   {
      mBackgroundColor = clr;
   }

   const Colorf& Widget::getBackgroundColor() const
   {
      return mBackgroundColor;
   }

   void Widget::setForegroundColor(const Colorf& clr)
   {
      mForegroundColor = clr;
   }

   const Colorf& Widget::getForegroundColor() const
   {
      return mForegroundColor;
   }

   void Widget::setFont(const gltext::FontPtr& font)
   {
      mFont = font;
   }

   const gltext::FontPtr& Widget::getFont() const
   {
      return mFont;
   }

   WidgetContainerPtr Widget::getParent() const
   {
      return boost::make_shared(mParent);
   }

   bool Widget::contains(const Point& p) const
   {
      return (p.x >= 0 && p.x < mSize.getWidth() &&
              p.y >= 0 && p.y < mSize.getHeight());
   }

   Point Widget::getScreenPosition() const
   {
      Point p = getPosition();
      WidgetContainerPtr parent = getParent();
      while (parent)
      {
         p += parent->getPosition();
         parent = parent->getParent();
      }
      return p;
   }

   bool Widget::hasFocus()
   {
      WidgetContainerPtr parent = getParent();
      WidgetPtr child = getSelf();
      while (parent)
      {
         if (parent->getFocus() != child)
         {
            return false;
         }
         child = parent;
         parent = parent->getParent();
      }
      //      puts("A widget has focus!");
      return true;
   }

   void Widget::setParent(WidgetContainerPtr parent)
   {
      mParent = parent;
   }

   boost::shared_ptr<Widget> Widget::getSelf()
   {
      return boost::make_shared(mSelf);
   }

   void Widget::setSelf(boost::shared_ptr<Widget> new_self)
   {
      mSelf = new_self;
   }

}
