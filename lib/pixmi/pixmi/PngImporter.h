
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     PngImporter class     =-
//
// Description: "Importer for PNG files.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PngImporter.h,v $
//    $Date: 2002-01-17 00:04:58 $
//    $Revision: 1.1.1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
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
#ifndef PNG_IMPORTER_INCLUDED
#define PNG_IMPORTER_INCLUDED

#include "Image.h"
#include "ImageImporter.h"
#include "PngChunk.h"

namespace pixmi
{

//: PngImporter
// Load an image file into an Image object
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   PngImporter png_import;
//   png_import( "bugs.png", image );
// 
// alternately, you can call operator() this way:
//   png_import.operator()( "bugs.png", image );
//
class PngImporter : public ImageImporter
{   
public:
   //: Default constructor
   PngImporter();
      
   //: Destructor
   virtual ~PngImporter();

   void convertToImage( PngChunk& headerChunk, PngChunk& dataChunk, Image& image );

   //: Save the image as "filename"
   //  returns true or false for successful or unsuccessful
   virtual bool load( const char* const filename, Image& image );
   
   //: a string that describes the files supported by this importer
   virtual const char* const   description() const;
};


} // namespace
#endif
