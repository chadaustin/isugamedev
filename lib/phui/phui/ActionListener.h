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
 * File:          $RCSfile: ActionListener.h,v $
 * Date modified: $Date: 2002-04-28 15:51:59 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Josh Carlson, Ben Scott
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
#ifndef PHUI_ACTION_LISTENER_H
#define PHUI_ACTION_LISTENER_H

#include "Widget.h"

namespace phui
{
   /**
    * Describes a generic action event.
    */
   class ActionEvent
   {
   public:
      /**
       * Creates a new action event using the given source widget.
       *
       * @param src     
       */
      ActionEvent(Widget* src)
         : mSource(src)
      {}

      /**
       * Gets the source widget that fired this event.
       *
       * @return  the source widget
       */
      Widget* getSource() const
      {
         return mSource;
      }

   private:
      /// The source of the event.
      Widget* mSource;
   };

   /**
    * Interface to a class that wishes to receive action events from a widgets.
    */
   class ActionListener
   {
   public:
      virtual ~ActionListener() {}

      /**
       * Notifies this listener that the source object has fired the given
       * action event.
       *
       * @param evt  the generated event
       */
      virtual void onAction(const ActionEvent& evt) = 0;
   };
}

#endif
