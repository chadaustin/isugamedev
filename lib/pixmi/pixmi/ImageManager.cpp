

//////////////////////////////////////////////////////////////////////////////
//
//                         -=     Image Manager     =-
//
//  Description:  same interface as most application's "File" menu.
//             Save, Load, Save As, Etc...
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ImageManager.cpp,v $
//    $Date: 2002-01-17 00:04:59 $
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

#include <iostream>
#include "CFileIO.h"
#include "Defines.h"
#include "ImageManager.h"

namespace pixmi
{

//: Load the file "filename"
//  returns true or false for successful or unsuccessful
//  writes the image to your Image object on success
bool ImageManager::load( const char* const filename, Image& image )
{
   if (CFileIO::fileExists( filename ) == false)
   {
      //Log(0) << "ImageManager: File doesn't exist\n" << flush;
      return false;
   }

   ImageImporter* ii = this->getImporter( filename );
   if (ii != NULL)
   {
      return (*ii).load( filename, image );
   } 

   //Log(0) << "ImageManager: Couldn't load image. No importer registered for this type.\n" << flush;
   return false;
}

//: Save the file as "filename"
//  QUESTION: should I not write the file if it already exists???
//  returns true or false for successful or unsuccessful
//  writes the Image to it's original filename (Image::name())
bool ImageManager::save( const char* const filename, const Image& image )
{
   if (CFileIO::fileExists( filename ) == true)
   {
      // rethink this... xxx kevin
      pixmi::Alert( CFileIO::fileExists( filename ) != true, "ImageManager: File already exists, delete it first" );
      return false;
   }

   ImageExporter* ie = this->getExporter( filename );
   if (ie != NULL)
   {
      return (*ie).save( filename, image );
   } 

   //Log(0) << "ImageManager: Couldn't save image, unsupported type or other error\n" << flush;
   return false;
}

////////////////////////////////////////////////////////////////////////////////////
// Import stuff
////////////////////////////////////////////////////////////////////////////////////


//: Add an Import to the Manager's inventory.
void ImageManager::addImporter(ImageImporter& importer)
{
   std::cout<<"Registering \""<<importer.description()<<"\" importer.\n"<<std::flush;
   
   int size = _importers.size();
   _importers.push_back( &importer );
}

//: get the newest Import in the Store that can load the filename
ImageImporter* ImageManager::getImporter( const char* const filename )
{
   if (_importers.size() == 0)
      std::cout<<"Warning... no importers installed\n"<<std::flush;
   
   ImageImporter* foundOne = NULL;

   for (int x = 0; x < _importers.size(); ++x)
   {
      if (_importers[x]->canHandle( filename ))
         foundOne = _importers[x];
   }

   return foundOne;
}

//: remove all Imports with the same description as "import"
void ImageManager::removeImporter(ImageImporter& importer)
{
   std::vector<ImageImporter*>::iterator iiIt;
   for (iiIt = _importers.begin(); iiIt != _importers.end(); ++iiIt)
   {
      if ( (*iiIt) == &importer)
      {
         _importers.erase( iiIt );
         return;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////////
// Export stuff
////////////////////////////////////////////////////////////////////////////////////

//: Add an Import to the Manager's inventory.
void ImageManager::addExporter(ImageExporter& exporter)
{
   std::cout<<"Registering \""<<exporter.description()<<"\" exporter.\n"<<std::flush;
   
   int size = _exporters.size();
   _exporters.push_back( &exporter );
}

//: get the newest exporter in the Store that can load the filename
ImageExporter* ImageManager::getExporter( const char* const filename )
{
   if (_exporters.size() == 0)
      std::cout<<"Warning... no exporters installed\n"<<std::flush;
   
   ImageExporter* foundOne = NULL;

   for (int x = 0; x < _exporters.size(); ++x)
   {
      if (_exporters[x]->canHandle( filename ))
         foundOne = _exporters[x];
   }

   return foundOne;
}

//: remove all Exporters with the same address as "exporter"
void ImageManager::removeExporter( ImageExporter& ie )
{
   std::vector<ImageExporter*>::iterator ieIt;
   for (ieIt = _exporters.begin(); ieIt != _exporters.end(); ++ieIt)
   {
      if ( (*ieIt) == &ie)
      {
         _exporters.erase( ieIt );
         return;
      }
   }
}

} // namespace
