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
 * File:          $RCSfile: FontRenderer.cpp,v $
 * Date modified: $Date: 2002-04-28 15:51:59 $
 * Version:       $Revision: 1.4 $
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
#include "FontRenderer.h"
#include <stdexcept>

namespace phui
{
   FontRenderer::FontRenderer(const Font& font)
      : mFont(font)
   {
      mRenderer = new GLTTPixmapFont(&(mFont.mFace));
      if ( ! mRenderer->create(mFont.getSize()) )
      {
         delete mRenderer;
         throw std::runtime_error("Failed to create font renderer");
      }
   }

   FontRenderer::FontRenderer(const FontRenderer& renderer)
      : mFont(renderer.mFont)
   {
      mRenderer = new GLTTPixmapFont(&(mFont.mFace));
      if ( ! mRenderer->create(mFont.getSize()) )
      {
         delete mRenderer;
         throw std::runtime_error("Failed to create font renderer");
      }
   }

   FontRenderer::~FontRenderer()
   {
      delete mRenderer;
   }

   void FontRenderer::draw(const std::string& text, int x, int y)
   {
      mRenderer->output(x, y, text.c_str());
   }

   const Font& FontRenderer::getFont() const
   {
      return mFont;
   }

   unsigned int FontRenderer::getAscent() const
   {
      return (getHeight() - getDescent());
   }

   unsigned int FontRenderer::getDescent() const
   {
      return (unsigned int)(-(mRenderer->getDescender()));
   }

   unsigned int FontRenderer::getHeight() const
   {
      return (unsigned int)mRenderer->getHeight();
   }

   unsigned int FontRenderer::getWidth(const std::string& text)
   {
      return (unsigned int)mRenderer->getWidth(text.c_str());
   }
}
