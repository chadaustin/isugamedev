/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Size.h,v $
 * Date modified: $Date: 2002-04-26 06:26:27 $
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
#ifndef PHUI_SIZE_H
#define PHUI_SIZE_H

#include "phuiCommon.h"

namespace phui
{
   /**
    * Class used to describe a size value.
    */
   class Size
   {
   public:
      /**
       * Creates a new Size object initialized to 0.
       */
      Size();

      /**
       * Creates a new Size object with the given values.
       *
       * @param width      the width of the size
       * @parma height     the height of the size
       */
      Size(int width, int height);

      /**
       * Creates an exact duplicate of the given Size object.
       *
       * @param size       the Size object to copy
       */
      Size(const Size& size);

      /**
       * Makes this size object a copy of the given size object.
       *
       * @param size       the Size object to copy
       */
      Size& operator=(const Size& size);

      /**
       * Compares this Size to the given Size object to see if they are equal.
       *
       * @param size       the Size to compare with.
       *
       * @return  true if they are equal, false otherwise
       */
      bool operator==(const Size& size) const;

      /**
       * Compares this Size to the given Size object to see if they are not
       * equal.
       *
       * @param size       the Size to compare with.
       *
       * @return  true if they are not equal, false otherwise
       */
      bool operator!=(const Size& size) const;

      /**
       * Gets the width of this size.
       */
      int getWidth() const
      {
         return mWidth;
      }

      /**
       * Gets the height of this size.
       */
      int getHeight() const
      {
         return mHeight;
      }

   private:
      /// Width of this size
      int mWidth;

      /// Height of this size
      int mHeight;
   };
}

#endif
