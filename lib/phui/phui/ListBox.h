/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ListBox.h,v $
 * Date modified: $Date: 2002-04-22 07:22:39 $
 * Version:       $Revision: 1.1 $
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
#ifndef PHUI_LISTBOX_H
#define PHUI_LISTBOX_H

#include "phuiCommon.h"
#include <string>
#include <vector>
#include <iostream>
#include "Widget.h"

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
       * Called whenever a mouse button has been pressed inside this listbox. In
       * this case, we want to find which text item was selected
       */
      void onMouseDown(InputButton button, const Point& p);

   private:
      /**
       * The items in the listbox
       */
      std::vector<std::string> mItems;

      /**
       * The selected item in the listbox, -1 = none
       */
      int mSelectedItem;
   };

} // namespace phui

#endif
