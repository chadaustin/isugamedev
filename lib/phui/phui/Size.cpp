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
 * File:          $RCSfile: Size.cpp,v $
 * Date modified: $Date: 2003-01-06 01:34:53 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "Size.h"

namespace phui
{
   Size::Size()
      : mWidth(0), mHeight(0)
   {}

   Size::Size(int width, int height)
      : mWidth(width), mHeight(height)
   {}

   Size::Size(const Size& size)
   {
      *this = size;
   }

   void Size::set(int width, int height)
   {
      mWidth = width;
      mHeight = height;
   }

   Size& Size::operator=(const Size& size)
   {
      mWidth = size.mWidth;
      mHeight = size.mHeight;
      return *this;
   }

   bool Size::operator==(const Size& size) const
   {
      if ((mWidth == size.mWidth) &&
          (mHeight == size.mHeight))
      {
         return true;
      }
      return false;
   }

   bool Size::operator!=(const Size& size) const
   {
      return (! operator==(size));
   }

   int Size::getWidth() const
   {
      return mWidth;
   }

   void Size::setWidth(int width)
   {
      mWidth = width;
   }

   int Size::getHeight() const
   {
      return mHeight;
   }

   void Size::setHeight(int height)
   {
      mHeight = height;
   }

   std::ostream& operator<<(std::ostream& out, const Size& size)
   {
      return out << "(" << size.getWidth() << ", " << size.getHeight() << ")";
   }
}
