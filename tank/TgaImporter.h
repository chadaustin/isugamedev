
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     TgaImport class     =-
//
// Description: "Importer for Targa files.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: TgaImporter.h,v $
//    $Date: 2001-09-10 15:50:17 $
//    $Revision: 1.2 $
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

//////////////////////////////////////////////////////////////////////////////
#ifndef TGA_IMPORTER_INCLUDED
#define TGA_IMPORTER_INCLUDED

#include "Image.h"

//: TgaImporter
// Load an image file into an Image object
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   TgaImporter tga_import;
//   tga_import( "bugs.tga", image );
// 
// alternately, you can call operator() this way:
//   tga_import.operator()( "bugs.tga", image );
//
class TgaImporter
{   
public:
   //: Default constructor
   TgaImporter();      
      
   //: Destructor
   virtual ~TgaImporter();
      
   //: Load the image "filename", loads into the Image data
   //  returns true or false for successful or unsuccessful
   virtual bool import( const char* const filename, Image& image ) const;   
   
   //: a string that describes the files supported by this importer
   virtual const char* const description() const;
   
private:
   // Read, and expand, one row of RLE data from the filestream.
   // data       - pointer to buffer to recieve uncompressed data.
   // bufferSize - buffer size in bytes
   // bpp        - bytes per pixel (8, 16, 24, 32)
   // fp         - file pointer, must be an opened file, ::use fseek to position at valid start of RLE row.
   static int ReadRLERow( unsigned char* data, const int& bufferSize, const int& bpp, FILE *fp );
};



#endif
