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
 * File:          $RCSfile: Rect.h,v $
 * Date modified: $Date: 2003-01-04 06:44:08 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_RECT_H
#define PHUI_RECT_H

namespace phui
{
   /**
    * Class used to describe a rectangular region.
    */
   class Rect
   {
   public:
      /**
       * Creates a new Rect at (0,0) width dimenions (0,0).
       */
      Rect();

      /**
       * Creates a new Rect object with the given values.
       *
       * @param x       the x position of the rect
       * @param y       the y position of the rect
       * @param width   the width side of the rect
       * @param height  the height side of the rect
       */
      Rect(int x, int y, int width, int height);

      /**
       * Creates an exact duplicate of the given Rect object.
       *
       * @param rect    the Rect object to copy
       */
      Rect(const Rect& rect);

      /**
       * Makes this rect object a copy of the given rect object.
       *
       * @param rect     the Rect object to copy
       */
      Rect& operator=(const Rect& rect);

      /**
       * Compares this Rect to the given Rect object to see if they are
       * equal.
       *
       * @param rect     the Rect to compare with.
       *
       * @return  true if they are equal, false otherwise
       */
      bool operator==(const Rect& rect) const;

      /**
       * Compares this Rect to the given Rect object to see if they are not
       * equal.
       *
       * @param rect     the Rect to compare with.
       *
       * @return  true if they are not equal, false otherwise
       */
      bool operator!=(const Rect& rect) const;

   public:
      /// x position of the upper-left corner of the rect
      int mX;

      /// y position of the upper-left corner of the rect
      int mY;

      /// width of the rect
      int mWidth;

      /// height of the rect
      int mHeight;
   };
}

#endif
