
//////////////////////////////////////////////////////////////////
//
//                     -=   PixmapFont: font loader     =-
//
// Definition: "font loader for Image based fonts"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PixmapFontImporter.h,v $
//    $Date: 2001-09-26 22:58:56 $
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
#ifndef PIX_FONT_IMPORTER
#define PIX_FONT_IMPORTER

#include <iostream>
#include <fstream>
#include "TgaImporter.h"
#include "Texture.h"
#include "GState.h"

namespace kev
{
   
class PixmapFontImporter
{
   public:
static void loadGlyphMap( const char* const filename, PixmapFont& font )
{
   float height = 6;
   int index = 0;
   PixmapFont::GlyphData mapping;
   FILE* fp = ::fopen( filename, "rb" );
   assert( fp != NULL );
   fscanf( fp, "%f", &height );
   font.setHeight( height );
   while (index != -4 )
   {
      fscanf( fp, "%d", &index );
      fscanf( fp, "%f", &mapping.width() );
      
      fscanf( fp, "%f %f", &mapping.t1[0], &mapping.t1[1] );
      fscanf( fp, "%f %f", &mapping.t2[0], &mapping.t2[1] );
      fscanf( fp, "%f %f", &mapping.t3[0], &mapping.t3[1] );
      fscanf( fp, "%f %f", &mapping.t4[0], &mapping.t4[1] );
      
      font.setGlyphData( index, mapping );
   }
   fclose( fp );
}

static void import( const char* const filename, PixmapFont& font )
{
   std::cout<<"Loading font file: "<<filename<<"\n"<<std::flush;
         
   std::ifstream fontFile( filename, std::ios::in );
   assert( fontFile.good() && "- file not found" );
   		
   char key[256], value[256];
   std::string file_name;

   // set the name
   font.setName( filename );
   
   for (int x = 0; x < 2; ++x)
   {
      fontFile>>key>>value;
      file_name = value;
      if ( std::string( key ) == "map" )
      {
         std::cout<<"- loading map file: "<<file_name.c_str()<<"\n"<<std::flush;
         loadGlyphMap( file_name.c_str(), font );
      }
      else if ( std::string( key ) == "image" )
      {
         std::cout<<"- loading image file: "<<file_name.c_str()<<"\n"<<std::flush;
         TgaImporter ti;
         Image* image = new Image;
         ti( file_name.c_str(), *image );
         
         kev::GState* gstate = new kev::GState;
         gstate->setName( file_name );
         gstate->texture.setImage( image );
         font.setGState( gstate );
      }
   }
   
   fontFile.close();
   
}

};

}// end namespace

#endif
