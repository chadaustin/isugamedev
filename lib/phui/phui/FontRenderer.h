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
 * File:          $RCSfile: FontRenderer.h,v $
 * Date modified: $Date: 2003-01-04 02:47:57 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_FONTRENDERER_H
#define PHUI_FONTRENDERER_H

#include "phuiCommon.h"
#include <gltext.h>
#include "Size.h"

namespace phui
{
   /**
    * Describes an object that knows how to render fonts. Additionally, you can
    * use the renderer to get information about the font itself.
    *
    * @see Font
    */
   class FontRenderer
   {
   public:
      /**
       * Creates a new font renderer for the given font.
       *
       * @param font    the font this renderer will use
       *
       * @throw std::runtime_error     failure to create the font renderer
       */
      FontRenderer(const gltext::FontPtr& font);

      /**
       * Creates a copy of the given font renderer.
       *
       * @param renderer   the renderer to copy
       *
       * @throw std::runtime_error     failure to create the font renderer
       */
      FontRenderer(const FontRenderer& renderer);
      ~FontRenderer();

      /**
       * Draws the given string at the given position.
       */
      void draw(const std::string& text, int x, int y);
      
      /**
       * Draws the given string at the given position within the given size
       * constraints.  If the string will not fit into the constraints, a new
       * size object that contains values that will fit to the string is 
       * returned
       * @param text the text to draw
       * @param x x coord to draw at
       * @param y y coord to draw at
       * @param size the size constraint of the message
       * @return the size of the object necessary for the text to fit inside
       */
      Size* draw(const std::string& text, int x, int y, const Size& size);
      /**
       * Gets the font being used by this renderer.
       */
      const Font& getFont() const;

      /**
       * Gets the amount by which characters of this font ascend above the
       * baseline.
       *
       * @return  the font's ascent in pixels
       */
      unsigned int getAscent() const;

//      unsigned int getMaxAscent() const;

      /**
       * Gets the amount by which characters of this font descent below the
       * baseline.
       *
       * @return  the font's descent in pixels
       */
      unsigned int getDescent() const;

//      unsigned int getMaxDescent() const;

      /**
       * Gets the height of the font. This is equal to the sum of the ascent and
       * descent.
       *
       * @return  the height of the font
       */
      unsigned int getHeight() const;

//      unsigned int getLeading() const;

//      unsigned int getWidth(char c) const;

      /**
       * Computes the width of the given text string if rendered with this
       * renderer.
       *
       * @param text    the text to compute the width of
       *
       * @return  the width of the text
       */
      unsigned int getWidth(const std::string& text);

   private:
      /// The font this renderer uses.
     
      gltext::FontRendererPtr mRenderer;
     
      /// The GLTT renderer for the font face.
      //GLTTPixmapFont* mRenderer;
   };
}

#endif
