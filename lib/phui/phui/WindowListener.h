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
 * File:          $RCSfile: WindowListener.h,v $
 * Date modified: $Date: 2003-01-04 02:31:03 $
 * Version:       $Revision: 1.2 $
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
 * File:          $RCSfile: WindowListener.h,v $
 * Date modified: $Date: 2003-01-04 02:31:03 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_WINDOW_LISTENER_H
#define PHUI_WINDOW_LISTENER_H

namespace phui
{
   class Window;

   /**
    * Describes an event that indicates that a window has changed it's status.
    */
   class WindowEvent
   {
   public:
      /**
       * Creates a new window event using the given source widget.
       *
       * @param src     the window that fired the event
       */
      WindowEvent(Window* src)
         : mSource(src)
      {}

      /**
       * Gets the source window that fired this event.
       *
       * @return  the source window
       */
      Window* getWindow() const
      {
         return mSource;
      }

   private:
      /// The source of the event.
      Window* mSource;
   };

   /**
    * Interface to a class that wishes to receive events from a window.
    */
   class WindowListener
   {
   public:
      virtual ~WindowListener() {}

      /**
       * Notifies this listener that the source window has opened.
       *
       * @param evt  the generated event
       */
      virtual void onWindowOpened(const WindowEvent& evt) = 0;

      /**
       * Notifies this listener that the source window has closed.
       *
       * @param evt  the generated event
       */
      virtual void onWindowClosed(const WindowEvent& evt) = 0;

      /**
       * Notifies this listener that the source window has gained the focus.
       *
       * @param evt  the generated event
       */
      virtual void onWindowFocused(const WindowEvent& evt) = 0;

      /**
       * Notifies this listener that the source window has lost the focus.
       *
       * @param evt  the generated event
       */
      virtual void onWindowUnfocused(const WindowEvent& evt) = 0;
   };
}

#endif
