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
 * File:          $RCSfile: Widget.h,v $
 * Date modified: $Date: 2003-01-05 09:18:58 $
 * Version:       $Revision: 1.34 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_WIDGET_H
#define PHUI_WIDGET_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <gltext.h>
#include "Color.h"
#include "Input.h"
#include "Insets.h"
#include "Point.h"
#include "Size.h"
#include "Utility.h"

namespace phui
{
   // forward declare so we can point to our parent
   class WidgetContainer;
   typedef boost::shared_ptr<WidgetContainer> WidgetContainerPtr;

   /**
    * Abstract base class for all Widgets.
    */
   class Widget
   {
      friend class WidgetContainer;
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
       * @return  the position of this widget
       */
      virtual const Point& getPosition() const;

      /**
       * Sets the position of this widget relative to its parent.
       *
       * @param x    the x position of this widget
       * @param y    the y position of this widget
       */
      virtual void setPosition(const Point& p);

      /**
       * Gets the size of this widget.
       *
       * @return  the size of this widget
       */
      virtual const Size& getSize() const;

      /**
       * Sets the size of this widget.
       *
       * @param size    the new size of the widget
       */
      void setSize(const Size& size);

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
      virtual void setEnabled(bool enabled);

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
      virtual void setVisible(bool visible);

      void show() { setVisible(true); }
      void hide() { setVisible(false); }

      /**
       * Sets the background color of this widget.
       *
       * @param clr     the new background color
       */
      virtual void setBackgroundColor(const Colorf& clr);

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
      virtual void setForegroundColor(const Colorf& clr);

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
      virtual void setFont(const gltext::FontPtr& font);

      /**
       * Gets the font for this widget.
       */
      virtual const gltext::FontPtr& getFont() const;

      /**
       * Gets the parent container for this widget or NULL if this
       * widget has no container.
       */
      WidgetContainerPtr getParent() const;

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

//   protected:
//      ///@{
//      /**
//       * Creates a new widget of the given type and makes sure that it has a
//       * pointer to itself.
//       */
//      template< class T >
//      static boost::shared_ptr<T> create(Type2Type<T> = Type2Type<T>())
//      {
//         boost::shared_ptr<T> obj(new T());
//         obj->setSelf(obj);
//         return obj;
//      }
//
//      template< class T, typename A1 >
//      static boost::shared_ptr<T> create(A1 arg1, Type2Type<T> = Type2Type<T>())
//      {
//         boost::shared_ptr<T> obj(new T(arg1));
//         obj->setSelf(obj);
//         return obj;
//      }
//      ///@}

   private:
      /// This method is private and should only be used by WidgetContainer.
      void setParent(WidgetContainerPtr parent);

   protected:
      /// Gets a shared pointer to this widget.
      boost::shared_ptr<Widget> getSelf();

      /**
       * Tells this object about the shared pointer to itself so that it can
       * keep a weak pointer to itself. This way it can return pointers to
       * 'this'.
       */
      void setSelf(boost::shared_ptr<Widget> new_self);

   private:
      /**
       * The position of the widget in pixels relative to its parent.
       */
      Point mPosition;

      /// The size of the widget in pixels.
      Size mSize;

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
      //Font mFont;
      gltext::FontPtr mFont;

      /**
       * The parent container for this widget.
       */
      boost::weak_ptr<WidgetContainer> mParent;

      /// The weak pointer to ourself.
      boost::weak_ptr<Widget> mSelf;
   };

   typedef boost::shared_ptr<Widget> WidgetPtr;
}

#endif
