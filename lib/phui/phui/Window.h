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
 * File:          $RCSfile: Window.h,v $
 * Date modified: $Date: 2005-01-25 17:28:52 $
 * Version:       $Revision: 1.20 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_WINDOW_H
#define PHUI_WINDOW_H

#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include "LayoutManager.h"
#include "WidgetContainer.h"
#include "WindowListener.h"

namespace phui
{
   class Window;
   typedef Loki::SmartPtrDef<Window>::type WindowPtr;
   
   class Window : public WidgetContainer
   {
   protected:
      /// Creates a window with an empty title.
      Window();

      /**
       * Creates a window with the given title.
       *
       * @param   title          the title for the window
       */
      Window(const std::string& title);

   public:
      virtual ~Window();

      /// Creates a window with an empty title.
      static WindowPtr create();

      /**
       * Creates a window with the given title.
       *
       * @param   title          the title for the window
       */
      static WindowPtr create(const std::string& title);

      void draw();

      /// Overloaded to fire window events.
      virtual void setVisible(bool visible);

      /**
       * Adds the given window listener that wishes to receive window events.
       */
      void addWindowListener(WindowListenerPtr listener);

      /**
       * Removes the given window listener for this button.
       */
      void removeWindowListener(WindowListenerPtr listener);

   private:
      /// Helper initializing method called by constructors.
      void init(const std::string& title, bool visible);

      /// Helper to fire a window opened event to all listeners.
      void fireWindowOpenedEvent();

      /// Helper to fire a window closed event to all listeners.
      void fireWindowClosedEvent();

   private:
      /// The title of the window.
      std::string mTitle;

      /// All listeners for this window.
      typedef std::list<WindowListenerPtr> ListenerList;
      typedef ListenerList::iterator ListenerIter;
      std::list<WindowListenerPtr> mListeners;
   };
}

#endif
