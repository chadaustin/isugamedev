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
 * File:          $RCSfile: BitmapRenderer.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "BitmapRenderer.h"
#include "GLPixelGlyph.h"

namespace gltext
{
   BitmapRenderer* BitmapRenderer::create(Font* font)
   {
      return new BitmapRenderer(font);
   }

   BitmapRenderer::BitmapRenderer(Font* font)
      : AbstractRenderer(font)
   {
   }

   GLGlyph*
   BitmapRenderer::makeGlyph(Glyph* glyph)
   {
      const int width  = glyph->getWidth();
      const int height = glyph->getHeight();
      const int offX   = glyph->getXOffset();
      const int offY   = glyph->getYOffset();
      u8* buffer = new u8[width * height];
      glyph->renderBitmap(buffer);

      return new GLPixelGlyph(offX, offY + getFont()->getAscent(),
                              width, height, buffer);
   }
}
