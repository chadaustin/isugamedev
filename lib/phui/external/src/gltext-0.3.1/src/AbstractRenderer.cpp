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
 * File:          $RCSfile: AbstractRenderer.cpp,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <algorithm>
#include <iostream>
#include "AbstractRenderer.h"

namespace gltext
{
   AbstractRenderer::AbstractRenderer(Font* font)
      : mFont(font)
   {
   }

   void GLTEXT_CALL AbstractRenderer::render(const char* text)
   {
      const int ascent  = mFont->getAscent();
      const int descent = mFont->getDescent();
      const int height  = ascent + descent + mFont->getLineGap();

      int penX = 0;
      int penY = 0;

      unsigned char last_character = 0;

      // Run through each char and generate a glyph to draw
      for (const char* itr = text; *itr; ++itr)
      {
         // newline?
         if (*itr == '\n')
         {
            penX = 0;
            penY += height;
            continue;
         }

         // Get the glyph for the current character
         Glyph* fontGlyph = mFont->getGlyph(*itr);
         if (!fontGlyph)
         {
            continue;
         }

         // Check the cache first
         GLGlyph* drawGlyph = mCache.get(fontGlyph);
         if (!drawGlyph)
         {
            // Cache miss. Ask this renderer to create a new one
            drawGlyph = makeGlyph(fontGlyph);
            if (!drawGlyph)
            {
               // AAACK! Couldn't create the glyph. Fail silently.
               continue;
            }
            mCache.put(fontGlyph, drawGlyph);
         }

         int kerning = mFont->getKerning(last_character, *itr);
         last_character = *itr;
         int old_x = penX;
         penX += kerning;

         // Now tell the glyph to render itself.
         drawGlyph->render(penX, penY);
         penX += fontGlyph->getAdvance();

         // Kerning shouldn't make us draw farther and farther to the
         // left...  this fixes the "sliding dot problem".
         penX = std::max(penX, old_x);
      }
   }

   int GLTEXT_CALL AbstractRenderer::getWidth(const char* text)
   {
      if (! text)
      {
         return 0;
      }

      int max_width = 0;
      int width = 0;

      unsigned char last_character = 0;

      // Iterate over each character adding its width
      for (const char* itr = text; *itr != 0; ++itr)
      {
         if (*itr == '\n')
         {
            width = 0;
            continue;
         }

         // Get the glyph for the current character
         Glyph* fontGlyph = mFont->getGlyph(*itr);
         if (fontGlyph)
         {
            int kerning = mFont->getKerning(last_character, *itr);
            last_character = *itr;
            width += kerning;
         
            // Add this glyph's advance
            width += fontGlyph->getAdvance();
            max_width = std::max(width, max_width);
         }
      }

      return max_width;
   }

   int GLTEXT_CALL AbstractRenderer::getHeight(const char* text)
   {
      const int ascent = mFont->getAscent();
      const int descent = mFont->getDescent();
      const int height = ascent + descent + mFont->getLineGap();
      return int(std::count(text, text + strlen(text), '\n') + 1) * height;
   }

   Font* GLTEXT_CALL AbstractRenderer::getFont()
   {
      return mFont.get();
   }
}
