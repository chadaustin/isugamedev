
//////////////////////////////////////////////////////////////////
//
//                     -=   TextToGeoSet     =-
//
// Definition: "Makes text that you can render.  creates a geoset of quads
//              each mapped with an Image of a letter in your text string. "
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: TextToGeoSet.h,v $
//    $Date: 2001-09-26 22:59:52 $
//    $Revision: 1.1 $
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

#ifndef TEXT_TO_GEOSET
#define TEXT_TO_GEOSET

#include "GeoSet.h"

namespace kev
{
   class TextToGeoSet
   {         
      public:
      static void convert( const std::string& text, PixmapFont& font, const Vec3<float>& color, GeoSet& gset )
      {
          gset.setNumPrims( text.size() );

          // init the num of verts of each glyph (4 == quad)
          std::vector<int> lengths;
          lengths.resize( text.size() );
          int x;
          for (x = 0; x < lengths.size(); ++x) { lengths[x] = 4; }

          gset.setPrimType( GeoSet::TRISTRIPS );
          gset.setPrimLengths( &lengths[0], text.size() );
          gset.allocate();

          std::vector<Vec3<float> > coords;
          std::vector<Vec4<float> > colors;
          std::vector<Vec2<float> > texCoords;
          std::vector<Vec3<float> > norms;
          std::vector<unsigned int>          cindex;
          float space = 0;
          float width = 0;
          float height = 0;
          for (x = 0; x < text.size(); ++x)
          {
             space += width;
             width = font.glyphData( text[x] ).width();
             height = font.height();
             coords.push_back( Vec3<float>( space, height, 0 ) );
             coords.push_back( Vec3<float>( space, 0, 0 ) );

             const PixmapFont::GlyphData& glyphData = font.glyphData( text[x] );
             texCoords.push_back( glyphData.t1 );
             texCoords.push_back( glyphData.t3 );
             texCoords.push_back( glyphData.t2 );
             texCoords.push_back( glyphData.t4 );

             cindex.push_back( x*2 );
             cindex.push_back( x*2 + 1 );
             cindex.push_back( x*2 + 2 );
             cindex.push_back( x*2 + 3 );
          }    
          coords.push_back( Vec3<float>( space + width, height, 0 ) );
          coords.push_back( Vec3<float>( space + width, 0, 0 ) );
          norms.push_back( Vec3<float>( 0.0f, 0.0f, 1.0f ) );
          colors.push_back( Vec4<float>( color[0], color[1], color[2], 1.0f ) );

          gset.setGstate( font.gstate() );

          gset.setAttr( GeoSet::COORD3, GeoSet::PER_VERTEX, coords[0].data(), &cindex[0] );
          gset.setAttr( GeoSet::COLOR4, GeoSet::OVERALL, colors[0].data(), NULL );
          gset.setAttr( GeoSet::NORMAL3, GeoSet::OVERALL, norms[0].data(), NULL );
          gset.setAttr( GeoSet::TEXCOORD2, GeoSet::PER_VERTEX, texCoords[0].data(), NULL );
      }
   };
}// end namespace

#endif
