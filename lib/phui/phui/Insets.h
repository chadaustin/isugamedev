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
 * File:          $RCSfile: Insets.h,v $
 * Date modified: $Date: 2005-01-25 01:42:03 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_INSETS_H
#define PHUI_INSETS_H

#include <iostream>

namespace phui
{
   /**
    * Class used to describe the internal insets of a widget.
    */
   class Insets
   {
   public:
      /**
       * Creates a new Insets object with all insets initialized to 0.
       */
      Insets();

      /**
       * Creates a new Insets object with the given values.
       *
       * @param left    the inset on the left side of the widget
       * @param right   the inset on the right side of the widget
       * @param top     the inset on the top side of the widget
       * @param bottom  the inset on the bottom side of the widget
       */
      Insets(int left, int right, int top, int bottom);

      /**
       * Creates an exact duplicate of the given Insets object.
       *
       * @param insets     the Insets object to copy
       */
      Insets(const Insets& insets);

      /// Sets the insets for this object.
      void set(int left, int right, int top, int bottom);

      /**
       * Makes this insets object a copy of the given insets object.
       *
       * @param insets     the Insets object to copy
       */
      Insets& operator=(const Insets& insets);

      /**
       * Compares this Insets to the given Insets object to see if they are
       * equal.
       *
       * @param insets     the Insets to compare with.
       *
       * @return  true if they are equal, false otherwise
       */
      bool operator==(const Insets& insets) const;

      /**
       * Compares this Insets to the given Insets object to see if
       * they are not equal.
       *
       * @param insets     the Insets to compare with.
       *
       * @return  true if they are not equal, false otherwise
       */
      bool operator!=(const Insets& insets) const;

      /// Gets width of inset left.
      int getLeft() const;

      /// Sets the width of the left inset
      void setLeft(int left);

      /// Gets width of inset right.
      int getRight() const;

      /// Sets the width of the right inset
      void setRight(int right);

      /// Gets width of inset top.
      int getTop() const;

      /// Sets the width of the top inset
      void setTop(int top);

      /// Gets width of inset bottom.
      int getBottom() const;

      /// Sets the width of the bottom inset
      void setBottom(int bottom);

   private:
      /// Inset on the left side.
      int mLeft;

      /// Inset on the right side.
      int mRight;

      /// Inset on the top side.
      int mTop;

      /// Inset on the bottom side.
      int mBottom;
   };

   std::ostream& operator<<(std::ostream& out, const Insets& insets);
}

#endif
