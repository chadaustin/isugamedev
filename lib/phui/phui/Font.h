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
 * File:          $RCSfile: Font.h,v $
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
#ifndef PHUI_FONT_H
#define PHUI_FONT_H

#include "phuiCommon.h"
#include <string>
#include <gltt/FTFace.h>

namespace phui
{
   class FontRenderer;

   /**
    * Represents a TrueType font face. You can render text in this font using
    * an associated FontRenderer.
    *
    * @see FontRenderer
    */
   class Font
   {
      friend FontRenderer;
   public:
      /// The font style. Italic and bold may be or'd together.
      enum STYLE
      {
         PLAIN    = 0x0,   ///< Plain formatting
         ITALIC   = 0x1,   ///< Italics formatting
         BOLD     = 0x2    ///< Bold formatting
      };
   public:
      /**
       * Creates a new font from the specified name, style and point size.
       *
       * @param name    the font name. This is the font face name.
       * @param style   the style constant for the font.
       * @param size    the point size of the font.
       *
       * @throw std::runtime_error  font does not exist.
       */
      Font( const std::string& name, const STYLE& style, unsigned int size );

      /**
       * Creates a copy of the given font.
       *
       * @param font    the font to copy
       *
       * @throw std::runtime_error  font does not exist.
       */
      Font( const Font& font );

      /**
       * Gets the name of the font.
       *
       * @return  the name of the font.
       */
      const std::string& getName() const;

      /**
       * Gets the style of the font.
       *
       * @return  the style of the font.
       */
      const STYLE& getStyle() const;

      /**
       * Gets the size of the font.
       *
       * @return  the size of the font.
       */
      unsigned int getSize() const;

      /**
       * Tests if this font is bold.
       *
       * @return  true if the font is bold, false otherwise
       */
      bool isBold() const;

      /**
       * Tests if this font is italic.
       *
       * @return  true if the font is italic, false otherwise
       */
      bool isItalic() const;

      /**
       * Tests if this font is plain.
       *
       * @return  true if the font is plain, false otherwise
       */
      bool isPlain() const;

      /**
       * Makes this font a copy of the given font.
       *
       * @param font    the font to copy
       *
       * @return  a reference to this font after modification.
       *
       * @throw std::runtime_error  font does not exist.
       */
      Font& operator=( const Font& font );

   private:
      /// Font name
      std::string mName;

      /// Font style
      STYLE mStyle;

      /// Font point size
      unsigned int mSize;

      /// GLTT font face
      FTFace mFace;
   };
}

#endif
