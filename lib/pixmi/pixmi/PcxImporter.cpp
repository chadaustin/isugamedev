
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     PcxImport class     =-
//
// Description: "Imports a ZSoft PCX image.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PcxImporter.cpp,v $
//    $Date: 2002-04-18 19:04:06 $
//    $Revision: 1.3 $
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

#include <iostream>       // for std::cout and std::flush
#include <string>         // for std::string
#include "Defines.h"      // needed for pixmi::byteReverse()
#include "CFileIO.h"      // needed to write out binary data with proper endianness.

#include "PcxImporter.h"   // my header

using std::cout;
using std::flush;

//////////////////////////////////////////////
///  Public Members:
/////////////////////////////////////////////
namespace pixmi
{
//: Default constructor
PcxImporter::PcxImporter() : ImageImporter()
{
   this->addExtension( "pcx" );
}

//: Destructor
PcxImporter::~PcxImporter()
{
}

//: a string that describes the files supported by this importer
const char* const PcxImporter::description() const
{
   return "ZSoft PCX Image";
}

//: Load the file "filename"
//  returns true or false for successful or unsuccessful
//  returns an Image object
bool PcxImporter::load( const char* const filename, Image& image )
{
   if (!CFileIO::fileExists( filename ))
   {
      std::cout<<"File doesn't exist!\n"<<std::flush;
      return false;
   }

   FILE *f;

   f = fopen(filename, "rb");
   if (f == NULL)
   {
      printf("Could not load %s texture.\n", filename);
      return NULL;
   }
   else
   {
      image.setName( filename );
   }

   // manufacturer ID
   unsigned char magik;
   CFileIO::ReadByte( f, magik );
   
   if (magik != 0x0A)
   {
      fclose(f);
      pixmi::Alert( magik != 0x0A, "Invalid file magic." );
      return false;
   }

   // version flag
   unsigned char version;
   CFileIO::ReadByte( f, version );
   // should be 5: this indicates 24 bit / Version 3.0 PC Paintbrush image.

   // encoding flag
   unsigned char encoding;
   CFileIO::ReadByte( f, encoding );
   if (encoding != 1)
   {
      fclose(f);
      pixmi::Alert( encoding != 1, "This file uses an encoding format not in the PCX specification (must be RLE)" );
      return false;
   }

   //check for 8bit color planes
   unsigned char BitsPerPixel;
   CFileIO::ReadByte( f, BitsPerPixel );
   if (BitsPerPixel != 8)
   {
      fclose(f);
      printf("%s does not have 8bit color planes.\n", filename);
      return false;
   }

   //get xmin, ymin, xmax, ymax
   unsigned short xmin, ymin, xmax, ymax;
   CFileIO::ReadShort( CFileIO::LITTLE, f, xmin );
   CFileIO::ReadShort( CFileIO::LITTLE, f, ymin );
   CFileIO::ReadShort( CFileIO::LITTLE, f, xmax );
   CFileIO::ReadShort( CFileIO::LITTLE, f, ymax );
   
   int width  = (xmax + 1) - xmin;
   int height = (ymax + 1) - ymin;

   //skip DPI values
   unsigned long dpi;
   CFileIO::ReadLong( CFileIO::LITTLE, f, dpi );

   //read 16 color pallete junk
   unsigned char r, g, b;
   int count = 0;
   for (count = 0; count < 16; ++count)
   {
      CFileIO::ReadByte( f, r );
      CFileIO::ReadByte( f, g );
      CFileIO::ReadByte( f, b );
   }

   // reserved #1
   unsigned char reserved1;
   CFileIO::ReadByte(f, reserved1);

   //check color planes
   unsigned char channels;
   CFileIO::ReadByte( f, channels );
   unsigned int bpp = channels * 8;
   if (bpp != 24)
   {
      fclose(f);
      printf("%s is not 24bpp.\n", filename);
      return false;
   }

   //get the bytes per line
   unsigned short bytes_per_line;
   CFileIO::ReadShort( CFileIO::LITTLE, f, bytes_per_line );

   //skip some more junk
   unsigned char junk;
   for (count=0; count<60; count++)
      CFileIO::ReadByte( f, junk );

   //allocate storage for data here
   int alignment = 1;
   image.reserve( width, height, bpp, channels, alignment);
   
   // read RLE data
   int rgb = 0;
   unsigned char token = 0;
   int x, xx;
   for (int y = height - 1; y >= 0; --y)
   {
      x = xx = rgb = 0;
      while ( x < bytes_per_line * image.channels() )  //width * channels
      {
         CFileIO::ReadByte( f, token );
         if ((token & 0xC0) == 0xC0)
         {
            count = (token & 0x3F);
            CFileIO::ReadByte( f, token );
         }
         else
            count = 1;
         while (count--)
         {
            if (xx < width)
            {
               image.row( y )[xx * 3 + rgb] = token;
            }
            x++;
            if (x == bytes_per_line)
            {
               xx = 0;
               rgb = 1;
            }
            else if (x == bytes_per_line*2)
            {
               xx = 0;
               rgb = 2;
            }
            else
               xx++;
         }
      }
   }
   ::fclose(f);

   return true;
}

} // namespace
