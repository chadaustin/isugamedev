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
 * File:          $RCSfile: FTFont.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <algorithm>
#include "FTFont.h"
#include "FTGlyph.h"

namespace gltext
{
   FTFont* FTFont::create(const char* name, int size, int dpi)
   {
      FT_Library library;
      FT_Error error = FT_Init_FreeType(&library);
      if (error)
      {
         return 0;
      }

      // Try to open the face
      FT_Face face;
      error = FT_New_Face(library, name, 0, &face);
      if (error)
      {
         FT_Done_FreeType(library);
         return 0;
      }

      // Set the point size of this font
      error = FT_Set_Char_Size(face,
                               size * 64, // width in 1/64 of points
                               0,         // height same as width
                               dpi,       // device horiz resolution (dpi)
                               dpi);      // device vert resolution (dpi)
      if (error)
      {
         FT_Done_FreeType(library);
         FT_Done_Face(face);
         return 0;
      }

      return new FTFont(name, size, dpi, library, face);
   }

   FTFont::FTFont(const char* name,
                  int size,
                  int dpi,
                  FT_Library library,
                  FT_Face face)
      : mName(name)
      , mSize(size)
      , mDPI(dpi)
      , mLibrary(library)
      , mFace(face)
   {
      std::fill(mGlyphMap, mGlyphMap + 256, (FTGlyph*)0);
   }

   FTFont::~FTFont()
   {
      // Free all of our cached glyphs
      for (int i = 0; i < 256; ++i) {
         delete mGlyphMap[i];
      }

      if (mFace)
      {
         FT_Done_Face(mFace);
         mFace = 0;
      }

      if (mLibrary)
      {
         FT_Done_FreeType(mLibrary);
         mLibrary = 0;
      }
   }

   const char*
   FTFont::getName()
   {
      return mName.c_str();
   }

   Glyph*
   FTFont::getGlyph(unsigned char c)
   {
      // Have we already loaded a glyph?
      if (!mGlyphMap[c])
      {
         mGlyphMap[c] = FTGlyph::create(mFace, c);
      }
      return mGlyphMap[c];
   }

   int
   FTFont::getSize()
   {
      return mSize;
   }

   int
   FTFont::getDPI()
   {
      return mDPI;
   }

   int
   FTFont::getAscent()
   {
      return mFace->size->metrics.ascender >> 6;
   }

   int
   FTFont::getDescent()
   {
      // FT2 does descent in negative values. We want positive values.
      return mFace->size->metrics.descender >> 6;
   }

   int
   FTFont::getLineGap()
   {
      return (mFace->size->metrics.height >> 6) - getAscent() - getDescent();
   }

   int
   FTFont::getKerning(unsigned char l, unsigned char r)
   {
      int left  = FT_Get_Char_Index(mFace, l);
      int right = FT_Get_Char_Index(mFace, r);

      FT_Vector rv;
      if (FT_Get_Kerning(mFace, left, right, ft_kerning_default, &rv))
      {
         return 0;
      }
      else
      {
         return rv.x >> 6;
      }
   }
}
