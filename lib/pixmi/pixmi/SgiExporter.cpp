
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     SgiExport class     =-
//
// Description: "a class for loading of the SGI image format"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: SgiExporter.cpp,v $
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

#include <string>  // for std::string
#include <fstream.h> // this exporter write files using ofstream
#include "Defines.h"      // needed for pixmi::byteReverse()
#include "Endian.h" // for bytereverse and isLittleEndian
#include "SgiExporter.h"      // My Header


namespace pixmi
{
//////////////////////////////////////////////
///  Static Members:
/////////////////////////////////////////////

//: my tag, goes in the waste of space in the rgb header.
const unsigned char SgiExporter::_BIGDUMMY[404] = "This file generated with SgiExport, a file exporter plugin for imagespace written by Kevin Meinert: KevinMeinert@BigFoot.com";


//////////////////////////////////////////////
///  Public Members:
/////////////////////////////////////////////

//: Default constructor
SgiExporter::SgiExporter() : ImageExporter()
{
   this->addExtension( "rgb" );
   this->addExtension( "rgba" );
   this->addExtension( "sgi" );
   this->addExtension( "bw" );
}

//: a string that describes the files supported by this importer
const char* const SgiExporter::description() const
{
   return "Sgi Image";
}

//: Destructor
SgiExporter::~SgiExporter()
{
}

//: Save the image as "filename"
//  returns true or false for successful or unsuccessful
bool SgiExporter::save( const char* const filename, const Image& image )
{
   char   filler[80];
   unsigned char   storage = RGB_VERBATIM;
   unsigned char   channel = 0;
   unsigned long   n = 0;

   memset(filler, 0, 80);

   #ifdef WIN32
   ofstream hRGBFile( filename, ios::out | ios::binary, filebuf::openprot );
   #else
   ofstream hRGBFile( filename, ios::out, filebuf::openprot );
   #endif

   if (hRGBFile.rdbuf()->is_open() == false)
   {
      //Log(0)
      cout<< "The file could not be opened" << flush;
      return false;
   }

   _MAGIC = RGB_MAGIC;

   //1 for 1 color and 1 row, 
   //2 for 1 color and many rows, 
   //3 for many colors and rows
   if ( image.channels() == 1 && 
       (image.width() == 1 || image.height() == 1) )
      _DIMENSION = 1;
   else if ( image.channels() == 1 && image.width() > 1 && image.height() > 1 )
      _DIMENSION = 2;
   else _DIMENSION = 3;

   _XSIZE = image.width();
   _YSIZE = image.height();
   _ZSIZE = image.channels();
   _PIXMIN = 0;
   _PIXMAX = 255;
   _BPC = image.bpc();


   // SGI format is big endian, 
   // so will need to swap bytes if system architecture is little endian.
   if (pixmi::isLittleEndian())
   {
      //reverse anything that is not (unsigned char) size
      pixmi::byteReverse(_MAGIC);
      pixmi::byteReverse(_DIMENSION);
      pixmi::byteReverse(_XSIZE);
      pixmi::byteReverse(_YSIZE);
      pixmi::byteReverse(_ZSIZE);
      pixmi::byteReverse(_PIXMIN);
      pixmi::byteReverse(_PIXMAX);
      pixmi::byteReverse(_COLORMAP);
   }

   //write the header
   hRGBFile.write((char *)&_MAGIC,      sizeof(unsigned short));
   hRGBFile.write((char *)&storage,   sizeof(unsigned char) );
   hRGBFile.write((char *)&_BPC,      sizeof(unsigned char) );
   hRGBFile.write((char *)&_DIMENSION,   sizeof(unsigned short));
   hRGBFile.write((char *)&_XSIZE,      sizeof(unsigned short));
   hRGBFile.write((char *)&_YSIZE,      sizeof(unsigned short));
   hRGBFile.write((char *)&_ZSIZE,      sizeof(unsigned short));
   hRGBFile.write((char *)&_PIXMIN,   sizeof(unsigned long) );
   hRGBFile.write((char *)&_PIXMAX,   sizeof(unsigned long) );
   hRGBFile.write((char *) filler,      sizeof(unsigned char) * 4);
   strcpy(filler, image.name());
   hRGBFile.write((char *) filler,      sizeof(unsigned char) * 80);
   hRGBFile.write((char *)&_COLORMAP,   sizeof(unsigned long) );
   hRGBFile.write((char *) _BIGDUMMY,   sizeof(unsigned char) * 404);

   if (pixmi::isLittleEndian())
   {
      //re-reverse anything that is not unsigned char size
      pixmi::byteReverse(_MAGIC);
      pixmi::byteReverse(_DIMENSION);
      pixmi::byteReverse(_XSIZE);
      pixmi::byteReverse(_YSIZE);
      pixmi::byteReverse(_ZSIZE);
      pixmi::byteReverse(_PIXMIN);
      pixmi::byteReverse(_PIXMAX);
      pixmi::byteReverse(_COLORMAP);
   }
   
   unsigned long width = (unsigned long) _XSIZE;
   //unsigned long height = (unsigned long) _YSIZE;
   unsigned long channels = (unsigned long) _ZSIZE;

   // write it in RGB_VERBATIM format...

   //de-interlace the rgb data
   // in the file it should look like [rrrrrr(etc..)gggggg(etc..)bbbbbb(etc..)aaaaaa(etc..)]
   const int channelsXbpc = channels * _BPC;
   for(channel=0; channel < _ZSIZE; channel++) 
   {
      // write the image.
      for (int k = 0; k < image.height(); ++k)
      {
         const unsigned char* const row = image.row(k);
         
         for(n = channel; n < width * channelsXbpc; n += channelsXbpc) 
         {
            if (_BPC == sizeof(unsigned char))
               hRGBFile.write( &((unsigned char*)row)[n], _BPC);
            else 
               hRGBFile.write( &((unsigned char *)row)[n], _BPC);
         }
      }
   }

   hRGBFile.close();
   return true;
}

} // namespace
