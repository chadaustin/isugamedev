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
 * File:          $RCSfile: ListBox.h,v $
 * Date modified: $Date: 2002-04-28 15:51:59 $
 * Version:       $Revision: 1.4 $
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
#ifndef PHUI_LISTBOX_H
#define PHUI_LISTBOX_H

#include "phuiCommon.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "Widget.h"
#include "ListSelectionListener.h"

namespace phui {

   class ListBox : public Widget {
   public:
      /**
       * Creates a list with no items.
       */
      ListBox();

      /**
       * Destroys this listbox
       */
      virtual ~ListBox();

      /**
       * Draws this listbox
       */
      void draw();

      /**
       * Adds a string to the list box
       *
       * @param text       the text item to add to the list box
       */
      void add(const std::string& text);

      /**
       * Removes the item at the given index.
       */
      void remove(unsigned int idx);

      /**
       * Gets the item at the selected index.
       *
       * @param idx     the index of the item to retrieve
       * @pre idx < numItems
       */
      const std::string& get(unsigned int idx) const;

      /**
       * Gets the index of the selected item.
       *
       * @return  the index to the selected item; -1 if nothing is selected
       */
      int getSelectedIndex() const;

      /**
       * Called whenever a mouse button has been pressed inside this listbox. In
       * this case, we want to find which text item was selected
       */
      void onMouseDown(InputButton button, const Point& p);

      /**
       * Adds the given list selection listener that wishes to receive list
       * selection events.
       */
      void addListSelectionListener(ListSelectionListener* listener);

      /**
       * Removes the given action listener for this button.
       */
      void removeListSelectionListener(ListSelectionListener* listener);

   private:
      /// Helper to fire list selection events to listeners.
      void fireListSelectionEvent(int selectedIdx);

   private:
      /**
       * The items in the listbox
       */
      std::vector<std::string> mItems;

      /**
       * The selected item in the listbox, -1 = none
       */
      int mSelectedItem;

      /**
       * All listeners for this list.
       */
      typedef std::list<ListSelectionListener*> ListenerList;
      typedef ListenerList::iterator ListenerIter;
      std::list<ListSelectionListener*> mListeners;
   };

} // namespace phui

#endif
