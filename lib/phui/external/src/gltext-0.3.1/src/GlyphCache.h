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
 * File:          $RCSfile: GlyphCache.h,v $
 * Date modified: $Date: 2005-01-23 21:33:23 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_GLYPHCACHE_H
#define GLTEXT_GLYPHCACHE_H

#include <map>
#include "GLGlyph.h"

namespace gltext
{
   class Glyph;

   /**
    * Helper class for FontRenderer implementations to cache the rendering of a
    * particular glyph so they don't try to render it multiple times while
    * rendering a string.
    */
   class GlyphCache
   {
   public:
      ~GlyphCache()
      {
         // Delete all cached GLGlyphs.
         Cache::iterator itr;
         for (itr = mCache.begin(); itr != mCache.end(); ++itr)
         {
            delete itr->second;
         }
      }

      /**
       * Puts the given GLGlyph in the cache for the given FT2 glyph. Behavior
       * is undefined if either fontGlyph or glGlyph are NULL.
       */
      void put(Glyph* fontGlyph, GLGlyph* glGlyph)
      {
         mCache[fontGlyph] = glGlyph;
      }
      
      /**
       * Gets the GLGlyph for the given FT2 glyph. Returns NULL if the GL
       * rendered glyph is not yet in this cache.
       */
      GLGlyph* get(Glyph* glyph)
      {
         return mCache[glyph];
      }

   private:
      typedef std::map<Glyph*, GLGlyph*> Cache;

      /// The mapping between font glyphs and rendered glyphs.
      Cache mCache;
   };
}

#endif
