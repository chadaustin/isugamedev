/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: FontRendererCache.cpp,v $
 * Date modified: $Date: 2002-04-24 12:17:13 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Ben Scott
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

#include "FontRendererCache.h"

namespace phui
{
   FontRenderer* FontRendererCache::getFontRenderer(const Font& font) {
      for(unsigned int x=0;x<mCachedRenderers.size();++x) {
         if((font.getSize() == mCachedRenderers[x].first.getSize())
            && (font.getStyle() == mCachedRenderers[x].first.getStyle())
            && (font.getName() == mCachedRenderers[x].first.getName())) {
            // ooh, it exists already, give it to them
            return mCachedRenderers[x].second;
         }
      }
      std::pair<Font, FontRenderer*> toAdd(font, new FontRenderer(font));
      mCachedRenderers.push_back(toAdd);
      return toAdd.second;
   }

   FontRendererCache::FontRendererCache() { }

   FontRendererCache::~FontRendererCache() { }

   std::vector<std::pair<Font, FontRenderer*> > FontRendererCache::mCachedRenderers;
}
