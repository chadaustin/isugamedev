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
 * File:          $RCSfile: WindowAdapter.h,v $
 * Date modified: $Date: 2005-01-25 01:42:10 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_WINDOW_ADAPTER_H
#define PHUI_WINDOW_ADAPTER_H

#include <iostream>
#include "WindowListener.h"

namespace phui
{
   /**
    * Helper class the defines default implementations to all WindowListener
    * methods. Derive from this class if you want to be notified only of a
    * particular type of window event instead of all of them.
    *
    * @see WindowListener
    */
   class WindowAdapter : public WindowListener
   {
   public:
      WindowAdapter() {}
      ~WindowAdapter() {}

      /**
       * Notifies this listener that the source window has opened.
       *
       * @param evt  the generated event
       */
      void onWindowOpened(const WindowEvent& evt) {}

      /**
       * Notifies this listener that the source window has closed.
       *
       * @param evt  the generated event
       */
      void onWindowClosed(const WindowEvent& evt) {}

      /**
       * Notifies this listener that the source window has gained the focus.
       *
       * @param evt  the generated event
       */
      void onWindowFocused(const WindowEvent& evt) {}

      /**
       * Notifies this listener that the source window has lost the focus.
       *
       * @param evt  the generated event
       */
      void onWindowUnfocused(const WindowEvent& evt) {}
   };

   typedef Loki::SmartPtrDef<WindowAdapter>::type WindowAdapterPtr;
}

#endif
