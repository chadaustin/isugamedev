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
 * File:          $RCSfile: Insets.cpp,v $
 * Date modified: $Date: 2003-01-04 02:31:02 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "Insets.h"

namespace phui
{
   Insets::Insets()
      : mLeft(0), mRight(0), mTop(0), mBottom(0)
   {}

   Insets::Insets(int left, int right, int top, int bottom)
      : mLeft(left), mRight(right), mTop(top), mBottom(bottom)
   {}

   Insets::Insets(const Insets& insets)
   {
      *this = insets;
   }

   Insets& Insets::operator=(const Insets& insets)
   {
      mLeft = insets.mLeft;
      mRight = insets.mRight;
      mTop = insets.mTop;
      mBottom = insets.mBottom;
      return *this;
   }

   bool Insets::operator==(const Insets& insets) const
   {
      if ( (mLeft == insets.mLeft) &&
           (mRight == insets.mRight) &&
           (mTop == insets.mTop) &&
           (mBottom == insets.mBottom) )
      {
         return true;
      }
      return false;
   }

   bool Insets::operator!=(const Insets& insets) const
   {
      return (! operator==(insets));
   }
}
