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
 * File:          $RCSfile: Label.h,v $
 * Date modified: $Date: 2002-04-28 15:51:59 $
 * Version:       $Revision: 1.3 $
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
#ifndef PHUI_LABEL_H
#define PHUI_LABEL_H

#include "phuiCommon.h"
#include <string>
#include <iostream>
#include "Widget.h"

namespace phui {

   /**
    * A classic UI label widget.
    */
   class Label : public Widget {
   public:
      /**
       * Creates a new label with the given text at (0,0) with size (0,0).
       *
       * @param text   the text for the label, defaults to the no label
       */
      Label(const std::string& text = "");

      /**
       * Draws this label with its text.
       */
      virtual void draw();

      /**
       * Sets the text on this label to the given value.
       *
       * @param text      the text for this label
       */
      void setText( const std::string& text );

      /**
       * Gets the text on this label.
       *
       * @return  the text for this label
       */
      const std::string& getText() const;

   private:
      /**
       * The text on this label.
       */
      std::string mText;
   };

} // namespace phui

#endif
