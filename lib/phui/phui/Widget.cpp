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
 * Date modified: $Date: 2002-04-22 09:27:01 $
 * Version:       $Revision: 1.9 $
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
      : mWidth(0)
      , mHeight(0)
      , mEnabled(true)
      , mVisible(true)
      , mBackgroundColor(0,0,0,0)
      , mForegroundColor(1,1,1,1)
      , mFont("arial", Font::PLAIN, 12)
      , mParent(NULL)
   {
   }

   Widget::~Widget() {
   }

   Point Widget::getPosition() const {
      return mPosition;
   }

   void Widget::setPosition(const Point& p) {
      mPosition = p;
   }

   void Widget::getSize(int& width, int& height) const {
      width = mWidth;
      height = mHeight;
   }

   void Widget::setSize(int width, int height) {
      mWidth = width;
      mHeight = height;
   }

   const Insets& Widget::getInsets() const {
      return mInsets;
   }

   void Widget::setInsets(const Insets& insets) {
      mInsets = insets;
   }

   bool Widget::isEnabled() const {
      return mEnabled;
   }

   void Widget::setEnabled( bool enabled )
   {
      mEnabled = enabled;
   }

   bool Widget::isVisible() const {
      return mVisible;
   }

   void Widget::setVisible(bool visible) {
      mVisible = visible;
   }

   void Widget::setBackgroundColor(const Colorf& clr) {
      mBackgroundColor = clr;
   }

   Colorf Widget::getBackgroundColor() const {
      return mBackgroundColor;
   }

   void Widget::setForegroundColor(const Colorf& clr) {
      mForegroundColor = clr;
   }

   Colorf Widget::getForegroundColor() const {
      return mForegroundColor;
   }

   void Widget::setFont(const Font& font) {
      mFont = font;
   }

   const Font& Widget::getFont() const {
      return mFont;
   }

   WidgetContainer* Widget::getParent() const {
      return mParent;
   }

   bool Widget::contains(const Point& p) const {
      Point s = p - getPosition();
      return (s.x >= 0 && s.x < mWidth &&
              s.y >= 0 && s.y < mHeight);
   }

   Point Widget::getScreenPosition() const {
      Point p = getPosition();
      const WidgetContainer* parent = getParent();
      while (parent) {
         p += parent->getPosition();
         parent = parent->getParent();
      }
      return p;
   }
}
