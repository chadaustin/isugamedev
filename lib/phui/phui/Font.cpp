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
 * File:          $RCSfile: Font.cpp,v $
 * Date modified: $Date: 2003-01-04 02:31:01 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "Font.h"
#include <stdexcept>

namespace phui
{
   Font::Font( const std::string& name, const STYLE& style, unsigned int size )
      : mName( name ), mStyle( style ), mSize( size )
   {
      std::string filename = mName + ".ttf";
      if ( ! mFace.open(filename.c_str()) )
      {
         throw std::runtime_error("Font '" + filename + "' does not exist.");
      }
   }

   Font::Font( const Font& font )
      : mName( font.mName ), mStyle( font.mStyle ), mSize( font.mSize )
   {
      std::string filename = mName + ".ttf";
      if ( ! mFace.open(filename.c_str()) )
      {
         throw std::runtime_error("Font does not exist.");
      }
   }

   const std::string& Font::getName() const
   {
      return mName;
   }

   const Font::STYLE& Font::getStyle() const
   {
      return mStyle;
   }

   unsigned int Font::getSize() const
   {
      return mSize;
   }

   bool Font::isBold() const
   {
      return ((mStyle & BOLD) == BOLD);
   }

   bool Font::isItalic() const
   {
      return ((mStyle & ITALIC) == ITALIC);
   }

   bool Font::isPlain() const
   {
      return (mStyle == PLAIN);
   }

   Font& Font::operator=(const Font& font)
   {
      mName = font.mName;
      mStyle = font.mStyle;
      mSize = font.mSize;
      std::string filename = mName + ".ttf";
      if ( ! mFace.open(filename.c_str()) )
      {
         throw std::runtime_error("Font does not exist.");
      }
      return *this;
   }
}
