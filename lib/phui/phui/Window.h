/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Window.h,v $
 * Date modified: $Date: 2003-01-04 02:31:03 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
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
 * Date modified: $Date: 2003-01-04 02:31:03 $
 * Version:       $Revision: 1.13 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_WINDOW_H
#define PHUI_WINDOW_H

#include "phuiCommon.h"
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include "WidgetContainer.h"
#include "WindowListener.h"

namespace phui {

   class Window : public WidgetContainer {
   public:
      /**
       * Creates a window with an empty title.
       */
      Window();

      /**
       * Creates a window with the given title.
       *
       * @param title      the title for the window
       */
      Window( const std::string& title );

      virtual ~Window();

      void draw();

      /// Overloaded to fire window events.
      virtual void setVisible(bool visible);

      /**
       * Adds the given window listener that wishes to receive window events.
       */
      void addWindowListener(WindowListener* listener);

      /**
       * Removes the given window listener for this button.
       */
      void removeWindowListener(WindowListener* listener);

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
      typedef std::list<WindowListener*> ListenerList;
      typedef ListenerList::iterator ListenerIter;
      std::list<WindowListener*> mListeners;
   };

} // namespace phui

#endif
