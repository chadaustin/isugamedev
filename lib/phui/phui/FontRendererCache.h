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
 * File:          $RCSfile: FontRendererCache.h,v $
 * Date modified: $Date: 2003-01-04 02:47:57 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_FONTRENDERERCACHE_H
#define PHUI_FONTRENDERERCACHE_H

#include "phuiCommon.h"
#include "FontRenderer.h"
#include <utility>
#include <vector>

namespace phui
{
   /**
    * Describes an object that helps cache rendered fonts.
    *
    * @see Font
    * @see FontRenderer
    */
   class FontRendererCache
   {
   public:
      /**
       * Gets a font renderer from the cache, creates one if it isn't available.
       */
      static FontRenderer* getFontRenderer(const Font& font);

   private:
      /**
       * This is a singleton. Use FontRendererCache::getFontRenderer() instead.
       */
      FontRendererCache();

      /**
       * Copies of singletons are prohibited. This constructor is not implemented
       * on purpose. Usage should cause a compile-time error.
       */
      FontRendererCache(const FontRenderer& renderer);

      /**
       * Copies of singletons are prohibited. This assignment operator is not
       * implemented on purpose. Usage should cause a compile-time error.
       */
      FontRendererCache operator=(const FontRendererCache& copy);
      ~FontRendererCache();

   private:
      static std::vector<std::pair<Font, FontRenderer*> > mCachedRenderers;

   };
}

#endif
