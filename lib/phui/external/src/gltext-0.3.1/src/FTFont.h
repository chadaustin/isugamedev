/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/*************************************************************** gltext-cpr beg
 *
 * GLText - OpenGL TrueType Font Renderer
 * GLText is (C) Copyright 2002 by Ben Scott
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
 * File:          $RCSfile: FTFont.h,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_FTFONT_H
#define GLTEXT_FTFONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "gltext.h"

namespace gltext
{
   class FTGlyph;

   /**
    * FreeType 2 implementation of the Font interface.
    */
   class FTFont : public RefImpl<Font>
   {
   public:
      /// Creates a new FreeType font with the given face name and
      /// point size.
      static FTFont* create(const char* name, int size, int dpi);

      FTFont(const char* name,
             int size,
             int dpi,
             FT_Library library,
             FT_Face face);

      /**
       * Destroys the font, freeing the owned FreeType face struct.
       */
      ~FTFont();

      const char* GLTEXT_CALL getName();

      /**
       * Gets the FT2 glyph for the given character. Returns NULL if this font
       * does not support the character requested.
       */
      Glyph* GLTEXT_CALL getGlyph(unsigned char c);

      int GLTEXT_CALL getSize();
      int GLTEXT_CALL getDPI();
      int GLTEXT_CALL getAscent();
      int GLTEXT_CALL getDescent();
      int GLTEXT_CALL getLineGap();
      int GLTEXT_CALL getKerning(unsigned char l, unsigned char r);

   private:
      /// The name of this font.
      std::string mName;

      /// The point size for this font.
      int mSize;

      /// The DPI used when the font was created.
      int mDPI;

      /// The FreeType 2 library handle.
      FT_Library mLibrary;

      /// The FreeType 2 face handle.
      FT_Face mFace;

      /// Map of characters to FTGlyphs.  This should be replaced with
      /// a std::map when we need characters larger than 8 bits.
      FTGlyph* mGlyphMap[256];
   };
}

#endif
