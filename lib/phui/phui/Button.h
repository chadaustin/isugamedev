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
 * Date modified: $Date: 2002-02-25 04:35:43 $
 * Version:       $Revision: 1.7 $
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
       * Creates a new button with no label at (0,0) with size (0,0).
       */
      Button();

      /**
       * Creates a new button with the given label at (0,0) with size (0,0).
       *
       * @param label      the label for the button
       */
      Button( const std::string& label );

      /**
       * Destroys this button.
       */
      virtual ~Button();

      /**
       * Draws this button with its label.
       */
      virtual void draw();

      /**
       * Sets the label on this button to the given value.
       *
       * @param label      the label for this button
       */
      void setLabel( const std::string& label );

      /**
       * Gets the label on this button.
       *
       * @return  the label for this button
       */
      const std::string& getLabel() const;

   private:
      /**
       * The label on this button.
       */
      std::string mLabel;
   };

   typedef boost::shared_ptr<Button> ButtonPtr;

} // namespace phui

#endif
