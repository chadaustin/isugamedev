/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Button.h,v $
 * Date modified: $Date: 2002-04-17 07:25:26 $
 * Version:       $Revision: 1.10 $
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
#ifndef PHUI_BUTTON_H
#define PHUI_BUTTON_H

#include "phuiCommon.h"
#include <string>
#include "Widget.h"

namespace phui {

   /**
    * A classic UI button widget.
    */
   class Button : public Widget {
   public:
      /**
       * Creates a new button with no text at (0,0) with size (0,0).
       */
      Button();

      /**
       * Creates a new button with the given text at (0,0) with size (0,0).
       *
       * @param text      the text for the button
       */
      Button( const std::string& text );

      /**
       * Destroys this button.
       */
      virtual ~Button();

      /**
       * Draws this button with its text.
       */
      virtual void draw();

      /**
       * Sets the text on this button to the given value.
       *
       * @param text      the text for this button
       */
      void setText( const std::string& text );

      /**
       * Gets the text on this button.
       *
       * @return  the text for this button
       */
      const std::string& getText() const;

      /**
       * Called whenever a mouse button has been pressed inside this button. In
       * this case, we want to set the button's down state so that it can update
       * its visual appearance and test if the next MouseUp event will be inside
       * this button.
       */
      virtual void onMouseDown(InputButton button, int x, int y);

      /**
       * Called whenever a mouse button has been released after it has been
       * pressed inside this button. If the button is released inside this
       * button then we will fire a ButtonPressed event, otherwise we'll just
       * toggle the button's down state.
       */
      virtual void onMouseUp(InputButton button, int x, int y);

   private:
      /**
       * The text on this button.
       */
      std::string mText;

      /**
       * Button down state. True if the button is down.
       */
      bool mButtonDown;
   };

} // namespace phui

#endif
