/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Widget.h,v $
 * Date modified: $Date: 2002-04-08 20:06:45 $
 * Version:       $Revision: 1.11 $
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

#ifndef PHUI_WIDGET_H
#define PHUI_WIDGET_H

#include "phuiCommon.h"
#include "Color.h"
#include "Input.h"


namespace phui {

   class Widget
   {
   protected:
      /**
       * Creates a new widget with width and height 0 and size (0,0).
       */
      Widget()
         : mX(0), mY(0), mWidth(0), mHeight(0), mEnabled(true), mVisible(true),
           mBackgroundColor(0,0,0,0), mForegroundColor(1,1,1,1)
      {}

      virtual ~Widget() {
      }

   public:
      /**
       * Draws this widget.
       */
      virtual void draw() = 0;

      /**
       * Gets the position of this widget relative to its parent.
       *
       * @param x    [out]    the x position of this widget
       * @param y    [out]    the y position of this widget
       */
      virtual void getPosition(int& x, int& y) const
      {
         x = mX;
         y = mY;
      }

      /**
       * Sets the position of this widget relative to its parent.
       *
       * @param x    the x position of this widget
       * @param y    the y position of this widget
       */
      virtual void setPosition(int x, int y)
      {
         mX = x;
         mY = y;
      }

      /**
       * Gets the size of this widget relative to its parent.
       *
       * @param width   [out]    the width of this widget
       * @param height  [out]    the height of this widget
       */
      virtual void getSize(int& width, int& height) const
      {
         width = mWidth;
         height = mHeight;
      }

      /**
       * Sets the position of this widget relative to its parent.
       *
       * @param width   the width of this widget
       * @param height  the height of this widget
       */
      virtual void setSize(int width, int height)
      {
         mWidth = width;
         mHeight = height;
      }

      /**
       * Tests if this widget is enabled.
       *
       * @return  true if the widget is enabled, false if disabled
       */
      virtual bool isEnabled() const
      {
         return mEnabled;
      }

      /**
       * Sets the enabled status of this widget.
       *
       * @param enabled    true to enabled the widget, false to disable it
       */
      virtual void setEnabled( bool enabled )
      {
         mEnabled = enabled;
      }

      /**
       * Tests if this widget is visible.
       *
       * @return  true if the widget is visible, false otherwise
       */
      virtual bool isVisible() const
      {
         return mVisible;
      }

      /**
       * Shows or hides this component depending on the parameter visible.
       *
       * @param visible    true to show this component, false to hide it
       */
      virtual void setVisible( bool visible )
      {
         mVisible = visible;
      }

      /**
       * Sets the background color of this widget.
       *
       * @param clr     the new background color
       */
      virtual void setBackgroundColor( const Colorf& clr )
      {
         mBackgroundColor = clr;
      }

      /**
       * Gets the background color of this widget.
       *
       * @return  the background color
       */
      virtual const Colorf& getBackgroundColor() const
      {
         return mBackgroundColor;
      }

      /**
       * Sets the foreground color of this widget.
       *
       * @param clr     the new foreground color
       */
      virtual void setForegroundColor( const Colorf& clr )
      {
         mForegroundColor = clr;
      }

      /**
       * Gets the foreground color of this widget.
       *
       * @return  the foreground color
       */
      virtual const Colorf& getForegroundColor() const
      {
         return mForegroundColor;
      }

      virtual bool hasFocus() { return false; }


      // external events
      virtual void onKeyDown(InputKey key) { }
      virtual void onKeyUp(InputKey key) { }
      virtual void onMouseDown(InputButton button) { }
      virtual void onMouseUp(InputButton button) { }
      virtual void onMouseMove(int x, int y) { }


   protected:
      /**
       * The x position of the widget in pixels relative to its parent.
       */
      int mX;

      /**
       * The y position of the widget in pixels relative to its parent.
       */
      int mY;

      /**
       * The width of the widget in pixels.
       */
      int mWidth;

      /**
       * The height of the widget in pixels.
       */
      int mHeight;

      /**
       * Whether this widget is enabled or disabled.
       */
      bool mEnabled;

      /**
       * Whether this widget is visible.
       */
      bool mVisible;

      /**
       * The background color.
       */
      Colorf mBackgroundColor;

      /**
       * The foreground color.
       */
      Colorf mForegroundColor;
   };

   typedef boost::shared_ptr<Widget> WidgetPtr;

} // namespace phui

#endif
