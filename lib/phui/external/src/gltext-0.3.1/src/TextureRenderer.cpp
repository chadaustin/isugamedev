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
 * File:          $RCSfile: TextureRenderer.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "TextureRenderer.h"
#include "GLTextureGlyph.h"
#include <iostream>
#include <iomanip>

namespace gltext
{
   TextureRenderer* TextureRenderer::create(Font* font, bool mipmap)
   {
      return new TextureRenderer(font, mipmap);
   }
   
   TextureRenderer::TextureRenderer(Font* font, bool mipmap)
      : AbstractRenderer(font)
      , mMipMap(mipmap)
   {
   }

   GLGlyph*
   TextureRenderer::makeGlyph(Glyph* glyph)
   {
      int width  = glyph->getWidth();
      int height = glyph->getHeight();
      int offX   = glyph->getXOffset();
      int offY   = glyph->getYOffset();
      u8* data = new u8[width * height];
      glyph->render(data);
      
      return new GLTextureGlyph(offX, offY + getFont()->getAscent(),
                                width, height, data, mMipMap);
   }
}
