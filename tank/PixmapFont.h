
//////////////////////////////////////////////////////////////////
//
//                     -=   PixmapFont     =-
//
// Definition: "Image based font (use with TextToGeoSet, and PixmapFontImporter)"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PixmapFont.h,v $
//    $Date: 2001-09-28 15:20:17 $
//    $Revision: 1.5 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////
#ifndef PIXMAP_FONT
#define PIXMAP_FONT

#include <string>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"

#include "Image.h"
#include "GState.h"

namespace kev
{
   class PixmapFont
   {
   public:
      PixmapFont() : mGstate( NULL ), mName( "pixmap_font" )
      {
         mMapping.resize( 256 );
      }

      virtual ~PixmapFont()
      {
         setGState( NULL );
         //std::cout<<"deleting PixmapFont "<<mName<<"\n"<<std::flush;
      }   

      class GlyphData
      {
      public:
         void setWidth( float w ) { mWidth = w; }
         //void setHeight( float h ) { mHeight = w; }
         //const float& height() const { return mHeight; }
         const float& width() const { return mWidth; }
         float& width() { return mWidth; }
         Vec2<float> t1, t2, t3, t4;
      private:
         float mWidth;
         //float mHeight;
      };

      void setName( const std::string& name ) { mName = name; }
      void setHeight( float height )
      {
         mHeight = height;
      }

      // Pixmap font owns the memory you give here, it will delete it.
      void setGState( kev::GState* gstate )
      {
         mGstate = gstate;
      }

      void setGlyphData( int x, GlyphData& mapping ) { assert( x < 256 && x >= 0 ); mMapping[x] = mapping; }

      const float& height() const { return mHeight; }
      const GlyphData& glyphData( int whichGlyph ) const { assert( whichGlyph < 256 && whichGlyph >= 0 ); return mMapping[whichGlyph]; }


      kev::GState* gstate() { assert( mGstate != NULL ); return mGstate; }
      const kev::GState* gstate() const { assert( mGstate != NULL ); return mGstate; }
   private:
      safe_ptr<kev::GState>   mGstate;
      std::vector<GlyphData>  mMapping;
      float                   mHeight;
      std::string             mName;
   };

} // end namespace

#endif
