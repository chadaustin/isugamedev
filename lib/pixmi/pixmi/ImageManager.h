

//////////////////////////////////////////////////////////////////
//
//                         -=    ImageManager    =-
//
// Definition: "mimics a load/save dialog box for images"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ImageManager.h,v $
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
#ifndef IMAGE_MANAGER_INCLUDE
#define IMAGE_MANAGER_INCLUDE

#include "Singleton.h"
#include "ImageImporter.h"
#include "ImageExporter.h"

namespace pixmi
{

//: a manager (Store) for saving and loading of images.
//  TODO: add support for image "requests", so 
//        that if an image is already loaded, 
//        then it just hands a reference to that image.
//        NOTE: you'd probably want this functionality in a separate class (keep it simple and stupid)
class ImageManager : public pixmi::Singleton<ImageManager>
{
public:
   //: Load the file "filename"
   //  returns true or false for successful or unsuccessful
   //  writes the image to your Image object on success
   bool load( const char* const filename, Image& image );

   //: Save the file as "filename"
   //  QUESTION: should I not write the file if it already exists???
   //  returns true or false for successful or unsuccessful
   //  writes the Image to it's original filename (Image::name())
   bool save( const char* const filename, const Image& image );
   
//: used mostly by importer plugins
public:
   //: Add an Importer to the Manager's inventory.
   void         addImporter( ImageImporter& ii );

   //: get the newest Importer in the Store associated with the filename
   ImageImporter*   getImporter( const char* const filename );

   //: remove the newest Importer with the same address as "import"
   void         removeImporter( ImageImporter& ii );

//: used mostly by exporter plugins
public:
   //: Add an Importer to the Manager's inventory.
   void         addExporter( ImageExporter& ie );

   //: get the newest exporter in the Store that can load the filename
   ImageExporter*   getExporter( const char* const filename );

   //: remove all Exporters with the same address as "exporter"
   void         removeExporter( ImageExporter& ie );

public:
   //: a list of registered image Importers.
   std::vector<ImageImporter*> _importers;

   //: a list of registered image Exporters.
   std::vector<ImageExporter*> _exporters;
};

} // namespace

#endif
