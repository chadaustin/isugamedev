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
 * Date modified: $Date: 2002-04-22 09:27:01 $
 * Version:       $Revision: 1.20 $
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
#include "Font.h"
#include "Input.h"
#include "Insets.h"
#include "Point.h"

namespace phui
{
   // forward declare so we can point to our parent
   class WidgetContainer;

   class Widget
   {
      friend WidgetContainer;
   protected:
      /**
       * Creates a new widget with width and height 0 and size (0,0).
       */
      Widget();

      virtual ~Widget();

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
      virtual Point getPosition() const;

      /**
       * Sets the position of this widget relative to its parent.
       *
       * @param x    the x position of this widget
       * @param y    the y position of this widget
       */
      virtual void setPosition(const Point& p);
      void setPosition(int x, int y) { setPosition(Point(x, y)); }

      /**
       * Gets the size of this widget relative to its parent.
       *
       * @param width   [out]    the width of this widget
       * @param height  [out]    the height of this widget
       */
      virtual void getSize(int& width, int& height) const;

      /**
       * Sets the position of this widget relative to its parent.
       *
       * @param width   the width of this widget
       * @param height  the height of this widget
       */
      virtual void setSize(int width, int height);

      /**
       * Gets the insets for this widget.
       *
       * @return  the insets
       */
      virtual const Insets& getInsets() const;

      /**
       * Sets the insets for the widget.
       *
       * @param insets     the insets
       */
      virtual void setInsets(const Insets& insets);

      /**
       * Tests if this widget is enabled.
       *
       * @return  true if the widget is enabled, false if disabled
       */
      virtual bool isEnabled() const;

      /**
       * Sets the enabled status of this widget.
       *
       * @param enabled    true to enabled the widget, false to disable it
       */
      virtual void setEnabled( bool enabled );

      /**
       * Tests if this widget is visible.
       *
       * @return  true if the widget is visible, false otherwise
       */
      virtual bool isVisible() const;

      /**
       * Shows or hides this component depending on the parameter visible.
       *
       * @param visible    true to show this component, false to hide it
       */
      virtual void setVisible( bool visible );

      /**
       * Sets the background color of this widget.
       *
       * @param clr     the new background color
       */
      virtual void setBackgroundColor( const Colorf& clr );

      /**
       * Gets the background color of this widget.
       *
       * @return  the background color
       */
      virtual Colorf getBackgroundColor() const;

      /**
       * Sets the foreground color of this widget.
       *
       * @param clr     the new foreground color
       */
      virtual void setForegroundColor( const Colorf& clr );

      /**
       * Gets the foreground color of this widget.
       *
       * @return  the foreground color
       */
      virtual Colorf getForegroundColor() const;

      /**
       * Sets the font to use for rendering text in this widget.
       *
       * @param font    the new font
       */
      virtual void setFont( const Font& font );

      /**
       * Gets the font for this widget.
       */
      virtual const Font& getFont() const;

      /**
       * Gets the parent container for this widget or NULL if this
       * widget has no container.
       */
      WidgetContainer* getParent() const;

      /**
       * Tests if the given point is contained within this widget where the
       * point is relative to this widget's coordinate system.
       *
       * @param p  the point to test
       * @return whether the test succeeded or not
       */
      bool contains(const Point& p) const;

      /**
       * Gets the position of the upper-left corner of this widget relative to
       * the screen's coordinate system.
       *
       * @return  the point
       */
      Point getScreenPosition() const;

      bool hasFocus();

      // external events
      virtual void onKeyDown(InputKey key) { }
      virtual void onKeyUp(InputKey key) { }
      virtual void onMouseDown(InputButton button, const Point& p) { }
      virtual void onMouseUp(InputButton button, const Point& p) { }
      virtual void onMouseMove(const Point& p) { }

   private:
      /**
       * The position of the widget in pixels relative to its parent.
       */
      Point mPosition;

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
       * The insets for this widget.
       */
      Insets mInsets;

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

      /**
       * The foreground font.
       */
      Font mFont;

      /**
       * The parent container for this widget.
       */
      WidgetContainer* mParent;
   };

} // namespace phui

#endif
