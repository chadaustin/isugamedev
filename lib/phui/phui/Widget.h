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
 * Date modified: $Date: 2002-04-15 09:42:33 $
 * Version:       $Revision: 1.15 $
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
#include "Font.h"

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
      virtual void getPosition(int& x, int& y) const;

      /**
       * Sets the position of this widget relative to its parent.
       *
       * @param x    the x position of this widget
       * @param y    the y position of this widget
       */
      virtual void setPosition(int x, int y);

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
       * @param insetX  [out]    the horizontal inset
       * @param insetY  [out]    the vertical inset
       */
      virtual void getInsets(int insetX, int insetY);

      /**
       * Sets the insets for the widget.
       *
       * @param insetX     the horizonal inset
       * @param insetY     the vertical inset
       */
      virtual void setInsets(int insetX, int insetY);

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
      virtual const Colorf& getBackgroundColor() const;

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
      virtual const Colorf& getForegroundColor() const;

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
       * Gets the parent container for this widget or NULL if this widget has no
       * container.
       */
      virtual const WidgetContainer* getParent() const;
      virtual WidgetContainer* getParent();

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
       * The horizontal inset.
       */
      int mInsetX;

      /**
       * The vertical inset.
       */
      int mInsetY;

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
