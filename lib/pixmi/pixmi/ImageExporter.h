
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     image exporter    =-
//
// Description: "generalized class type for all Image exporters"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ImageExporter.h,v $
//    $Date: 2002-01-17 00:04:59 $
//    $Revision: 1.1.1.1 $
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
#ifndef IMAGE_EXPORTER
#define IMAGE_EXPORTER

#include "Image.h"
#include "FileHandler.h"
namespace pixmi
{
//: TgaExporter
// Abstract file handler for exportation of Image objects to a file.
// Derived classes will be able to write an Image object out to file
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   /* now do some changes to the image, white noise, a fractal, etc.. */
//   TgaExporter tga_export;
//   tga_export( "bugs.tga", image );
// 
// alternately, you can call operator() this way:
//   tga_export.operator()( "bugs.tga", image );
//
class ImageExporter : public FileHandler
{
// construction
public:
   //: virtual destructor
   virtual ~ImageExporter() {}

// methods
public:
   //: Saves the image as "filename"
   //  returns true or false for successful or unsuccessful
   virtual bool   save( const char* const filename, const Image& image ) = 0;
};
} // namespace
#endif
