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
 * File:          $RCSfile: GLPixelGlyph.h,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_GLPIXELGLYPH_H
#define GLTEXT_GLPIXELGLYPH_H

#include "GLGlyph.h"

namespace gltext
{
   /**
    * Implementation of GLGlyph that handles pixel-based images. In other words,
    * the contents of this glyph's data are blitted to the screen.
    */
   class GLPixelGlyph : public GLGlyph
   {
   public:
      /**
       * Creates a new OpenGL ready glyph with the given data. This glyph will
       * take ownership of the data memory.
       */
      GLPixelGlyph(int offX, int offY, int width, int height, u8* data);

      /**
       * Frees memory used by this glyph.
       */
      ~GLPixelGlyph();

      /**
       * Draws this glyph using the given pen position.
       */
      void render(int penX, int penY) const;

   private:
      int mOffsetX;
      int mOffsetY;
      int mWidth;
      int mHeight;
      u8* mData;
   };
}

#endif
