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
 * File:          $RCSfile: GLPixelGlyph.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "GLPixelGlyph.h"
#include "OpenGL.h"

namespace gltext
{
   GLPixelGlyph::GLPixelGlyph(int offx, int offy,
                              int width, int height, u8* data)
      : mOffsetX(offx), mOffsetY(offy)
      , mWidth(width), mHeight(height)
   {
      // align the rows in the pixel buffer to 4-byte boundaries
      int pitch = (width + 3) / 4 * 4;
      mData = new u8[pitch * height];
      memset(mData, 0, pitch * height);
      for (int y = 0; y < height; ++y)
      {
         memcpy(mData + pitch * y,
                data + width * (height - y - 1),
                width);
      }
      delete[] data;
   }

   GLPixelGlyph::~GLPixelGlyph()
   {
      delete[] mData;
   }

   void GLPixelGlyph::render(int penX, int penY) const
   {
      // Move the raster position to the right location and blit the glyph
      // image to the buffer.
      glRasterPos2i(penX + mOffsetX, penY + mHeight + mOffsetY);
      glDrawPixels(mWidth, mHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, mData);
   }
}
