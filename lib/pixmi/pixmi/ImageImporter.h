
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     image importer    =-
//
// Description: "generalized class type for all Image loaders"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ImageImporter.h,v $
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
#ifndef IMAGE_IMPORTER_INCLUDED
#define IMAGE_IMPORTER_INCLUDED

#include "Image.h"
#include "FileHandler.h"
namespace pixmi
{
//: ImageImporter
// Abstract file handler for importation of Image objects from a file.
// Derived classes from ImageImporter will load an image file into 
// an Image object
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
class ImageImporter : public FileHandler
{
// construction
public:
   //: virtual destructor
   virtual ~ImageImporter() {}

// methods
public:
   //: Load the file "filename"
   //  returns true or false for successful or unsuccessful
   //  returns an Image object
   virtual bool load( const char* const filename, Image& image ) = 0;
};

//////////////////////////////
// image importer properties.
//////////////////////////////
#include <iostream>
inline void outputImporterProperties( ImageImporter& ii )
{
   std::cout<<"Importer Type:      "<<ii.description()<<"\n"<<std::flush;
   std::cout<<"Related Extensions: ";
   for (int k = 0; k < ii.numberOfExtensionsSupported(); ++k)
   {
      std::cout<<'.'<<ii.extension(k)<<' ';
   }
   std::cout<<"\n"<<std::flush;
}
} // namespace
#endif
