
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     PcxImport class     =-
//
// Description: "Imports a ZSoft PCX image.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PcxImporter.h,v $
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
#ifndef PCX_IMPORTER_INCLUDED
#define PCX_IMPORTER_INCLUDED

#include "Image.h"
#include "ImageImporter.h"

namespace pixmi
{
   
//: PcxImporter
// Load an image file into an Image object
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   PcxImporter pcx_import;
//   pcx_import( "bugs.pcx", image );
// 
// alternately, you can call operator() this way:
//   pcx_import.operator()( "bugs.pcx", image );
//
class PcxImporter : public ImageImporter
{   
public:
   //: Default constructor
   PcxImporter();      
      
   //: Destructor
   virtual ~PcxImporter();
      
   //: Load the file "filename"
   //  returns true or false for successful or unsuccessful
   //  returns an Image object
   virtual bool            load( const char* const filename, Image& image );

   //: a string that describes the files supported by this importer
   virtual const char* const   description() const;
};
} // namespace
#endif
