/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TextField.h,v $
 * Date modified: $Date: 2002-04-22 05:46:26 $
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
#ifndef PHUI_TEXTFIELD_H
#define PHUI_TEXTFIELD_H

#include "phuiCommon.h"
#include <string>
#include <iostream>
#include "Widget.h"

namespace phui {

   /**
    * A classic UI textfield widget.
    */
   class TextField : public Widget {
   public:
      /**
       * Creates a new textfield with no text at (0,0) with size (0,0).
       */
      TextField();

      /**
       * Creates a new button with the given text at (0,0) with size (0,0).
       *
       * @param text      the text for the button
       */
      TextField( const std::string& text );

      /**
       * Destroys this button.
       */
      virtual ~TextField();

      /**
       * Draws this button with its text.
       */
      virtual void draw();

      /**
       * Sets the text on this field to the given value.
       *
       * @param text      the text for this field
       */
      void setText( const std::string& text );

      /**
       * Gets the text on this button.
       *
       * @return  the text for this field
       */
      const std::string& getText() const;

      /**
       * Called whenever a key has been pressed while this box has focus
       */
      virtual void onKeyDown(InputKey key);

   private:
      /**
       * The text in this field.
       */
      std::string mText;

   };

} // namespace phui

#endif
