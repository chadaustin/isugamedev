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
 * File:          $RCSfile: ActionListener.h,v $
 * Date modified: $Date: 2005-01-23 21:46:47 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
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
      ActionEvent(WidgetPtr src)
         : mSource(src)
      {}

      /**
       * Gets the source widget that fired this event.
       *
       * @return  the source widget
       */
      WidgetPtr getSource() const
      {
         return mSource;
      }

   private:
      /// The source of the event.
      WidgetPtr mSource;
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

   typedef Loki::SmartPtrDef<ActionListener>::type ActionListenerPtr;
}

#endif
