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
 * File:          $RCSfile: Rect.cpp,v $
 * Date modified: $Date: 2005-01-25 17:28:50 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "Rect.h"

namespace phui
{
   Rect::Rect()
      : mX(0), mY(0), mWidth(0), mHeight(0)
   {}

   Rect::Rect(int x, int y, int width, int height)
      : mX(x), mY(y), mWidth(width), mHeight(height)
   {}

   Rect::Rect(const Rect& rect)
   {
      *this = rect;
   }

   Rect& Rect::operator=(const Rect& rect)
   {
      mX = rect.mX;
      mY = rect.mY;
      mWidth = rect.mWidth;
      mHeight = rect.mHeight;
      return *this;
   }

   bool Rect::operator==(const Rect& rect) const
   {
      if ( (mX == rect.mX) &&
           (mY == rect.mY) &&
           (mWidth == rect.mWidth) &&
           (mHeight == rect.mHeight) )
      {
         return true;
      }
      return false;
   }

   bool Rect::operator!=(const Rect& rect) const
   {
      return (! operator==(rect));
   }
}
