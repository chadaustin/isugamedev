
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     TgaExport class     =-
//
// Description: "Importer for Targa files.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: TgaExporter.cpp,v $
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

#include <string>
#include "Defines.h"      // needed for pixmi::byteReverse()
#include "CFileIO.h"      // needed to write out binary data with proper endianness.
#include "TgaHeader.h"         // the TGA header data structure
#include <stdio.h> // for feof

#include "TgaExporter.h"


namespace pixmi
{
//: Default constructor
TgaExporter::TgaExporter()
{
   this->addExtension( "tga" );
}
   
//: Destructor
TgaExporter::~TgaExporter()
{
}

//: Save the image as "filename"
//  returns true or false for successful or unsuccessful
bool TgaExporter::save( const char* const filename, const Image& image )
{
   FILE* fp = ::fopen( filename, "wb" );
   if (fp == NULL)
   {
      pixmi::Alert( fp != NULL, "Could not open file for writing" );
      return false;
   }

   // Fill out the TGA header.
   TGAHeader header;
   header.idLength = 0;   // length of ID string 
            // NOTE: some image proggies can't handle an idstring
   header.mapType = 0;               // color map type, if 1 then there is a palette. if 0, then there is no palette.
   header.imageType = 2;            // image type code 2 for compressed truecolor, 10 for uncompressed truecolor
   header.mapStart = 0;            // starting index of map 
   header.mapLength = 0;            // size of map in elements (next field is the element size.
   header.mapDepth = 0;            // width of map in bits 8, 15, 16, 24, 32
   header.xOrigin = 0;               // x-origin of image 
   header.yOrigin = 0;               // y-origin of image 
   header.imageWidth = image.width();   // width of image 
   header.imageHeight = image.height();// height of image 
   header.pixelDepth = image.bpp();   // bits per pixel 
   header.imageDesc = 0;            // image descriptor
   char idString[256] = "";   //some image proggies can't handle an idstring
               // NOTE: some image proggies can't handle an idstring
   
   // the first data to be written is the standard header based on the
   // original TGA specification.
   if ( CFileIO::WriteByte( fp, header.idLength ) < 0 ) return false;
   if ( CFileIO::WriteByte( fp, header.mapType ) < 0 ) return false;
   if ( CFileIO::WriteByte( fp, header.imageType ) < 0 ) return false;
   if ( CFileIO::WriteShort( CFileIO::LITTLE, fp, header.mapStart ) < 0 ) return false;
   if ( CFileIO::WriteShort( CFileIO::LITTLE, fp, header.mapLength ) < 0 ) return false;
   if ( CFileIO::WriteByte( fp, header.mapDepth ) < 0 ) return false;
   if ( CFileIO::WriteShort( CFileIO::LITTLE, fp, header.xOrigin ) < 0 ) return false;
   if ( CFileIO::WriteShort( CFileIO::LITTLE, fp, header.yOrigin ) < 0 ) return false;
   if ( CFileIO::WriteShort( CFileIO::LITTLE, fp, header.imageWidth ) < 0 ) return false;
   if ( CFileIO::WriteShort( CFileIO::LITTLE, fp, header.imageHeight ) < 0 ) return false;
   if ( CFileIO::WriteByte( fp, header.pixelDepth ) < 0 ) return false;
   if ( CFileIO::WriteByte( fp, header.imageDesc ) < 0 ) return false;
   if ( header.idLength )
   {
      // TODO: should i use ferror instead of feof to determine error?
      ::fwrite( idString, 1, header.idLength, fp );
      if ( feof( fp ) != 0 )
         return false;
   }

   // swap the red and blue for saving out to the file.
   // also strip off any padding that may be in the data (TGA's don't have padding)
   Image tempImage;
   tempImage.reserve( image.width(), image.height(), image.bpp(), image.channels() );
   for (int b = 0; b < image.height(); ++b)
   {
      const unsigned char* const sourceRow = image.row( b );
      unsigned char* const destRow = tempImage.row( b );
      for (int a = 0; a < image.width(); ++a)
      {
         destRow[a*tempImage.channels() + 0] = sourceRow[a*image.channels() + 2];
         destRow[a*tempImage.channels() + 1] = sourceRow[a*image.channels() + 1];
         destRow[a*tempImage.channels() + 2] = sourceRow[a*image.channels() + 0];
         if (tempImage.channels() == 4)
            destRow[a*tempImage.channels() + 3] = sourceRow[a*image.channels() + 3];
      }
   }   

   //: Write Truecolor UNcompressed
   if (header.imageType == 2)
   {
      // save it to the file uncompressed
      int size = ::fwrite( tempImage.data(), sizeof(unsigned char), tempImage.size(), fp );
      pixmi::Alert( size == tempImage.size(), "Couldn't write the entire image" );
   }


   //: Write Truecolor Compressed
   if (header.imageType == 10)
   {
      //: allocate plenty of data for one encoded scanline
      int ebs = tempImage.width() * tempImage.channels() * 2;
      unsigned char* encodedBuffer = new unsigned char[ebs];
      int rleCount = 0;

      for ( int i = 0; i < image.height(); ++i )
      {
         rleCount = TgaExporter::RLEncodeRow( tempImage.row( i ), tempImage.width(), tempImage.channels(), encodedBuffer );
         if ( ::fwrite( encodedBuffer, sizeof(unsigned char), rleCount, fp ) != rleCount )
         {
            pixmi::Alert( false, "Couldn't write all image data" );
            //return false;
         }
      }
      delete []encodedBuffer;
   }

   ::fclose( fp );

   return true;
}

//: a string that describes the files supported by this importer
const char* const TgaExporter::description() const
{
   return "Truevision Graphics Adapter";
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


//: Encode one scanline of data.
//  does compression using pixel by pixel RLE encoding
//
// unencodedBuffer - Source buffer (unencoded data)
// size             - Size of the source unencodedBuffer in bytes
// channels        - number of bytes per pixel, usually (in truecolor) one channel is one byte.  (channels == bytesPerPixel)
// encodedBuffer   - Dest Buffer (encodeded scan line) 
//
// Returns: Number of bytes in compressed scan line.
int TgaExporter::RLEncodeRow(const unsigned char* unencodedBuffer,
                      int size,
                      int channels,
                      unsigned char* encodedBuffer )      
{
   int            diffCount;         // pixel count until two identical 
   int            sameCount;         // number of identical adjacent pixels 
   int            encodedBufferSize;   // count of number of bytes encoded 

   encodedBufferSize = 0;
   while ( size > 0 )
   {
      diffCount = CountDiffPixels( unencodedBuffer, channels, size );
      sameCount = CountSamePixels( unencodedBuffer, channels, size );
      if ( diffCount > 128 ) diffCount = 128;
      if ( sameCount > 128 ) sameCount = 128;
      if ( diffCount > 0 )
      {
         // create a raw packet 
         *encodedBuffer++ = (char)(diffCount - 1);
         size -= diffCount;
         encodedBufferSize += (diffCount * channels) + 1;
         while ( diffCount > 0 )
         {
            *encodedBuffer++ = *unencodedBuffer++;
            if ( channels > 1 ) *encodedBuffer++ = *unencodedBuffer++;
            if ( channels > 2 ) *encodedBuffer++ = *unencodedBuffer++;
            if ( channels > 3 ) *encodedBuffer++ = *unencodedBuffer++;
            diffCount--;
         }
      }
      if ( sameCount > 1 )
      {
         // create a RLE packet 
         *encodedBuffer++ = (char)((sameCount - 1) | 0x80);
         size -= sameCount;
         encodedBufferSize += channels + 1;
         unencodedBuffer += (sameCount - 1) * channels;
         *encodedBuffer++ = *unencodedBuffer++;
         if ( channels > 1 ) *encodedBuffer++ = *unencodedBuffer++;
         if ( channels > 2 ) *encodedBuffer++ = *unencodedBuffer++;
         if ( channels > 3 ) *encodedBuffer++ = *unencodedBuffer++;
      }
   }
   return( encodedBufferSize );
}


// Count pixels in buffer until two identical adjacent ones found
// NOTE: im guessing that bpp is channels (or bytes per pixel)
int TgaExporter::CountDiffPixels( const unsigned char* p,
                        int bpp,
                        int pixCnt )
{
   unsigned long   pixel;
   unsigned long   nextPixel;
   int            n;

   n = 0;
   if ( pixCnt == 1 ) 
      return pixCnt;

   pixel = GetPixel( p, bpp );
   while ( pixCnt > 1 )
   {
      p += bpp;
      nextPixel = GetPixel( p, bpp );
      if ( nextPixel == pixel ) break;
      pixel = nextPixel;
      ++n;
      --pixCnt;
   }
   if ( nextPixel == pixel ) 
      return n;
   
   return (n + 1);
}

int TgaExporter::CountSamePixels( const unsigned char* p,
                        int bpp,
                        int pixCnt )
{
   unsigned long   pixel;
   unsigned long   nextPixel;
   int            n;

   n = 1;
   pixel = GetPixel( p, bpp );
   pixCnt--;
   while ( pixCnt > 0 )
   {
      p += bpp;
      nextPixel = GetPixel( p, bpp );
      if ( nextPixel != pixel ) break;
      ++n;
      --pixCnt;
   }
   return n;
}

// Retrieve a pixel value from a buffer.  The actual size and order
// of the bytes is not important since we are only using the value
// for comparisons with other pixels.
unsigned long TgaExporter::GetPixel( const unsigned char* p, int bpp )
{
   unsigned long   pixel;

   pixel = (unsigned long)*p++;
   while ( bpp-- > 1 )
   {
      pixel <<= 8;
      pixel |= (unsigned long)*p++;
   }
   return( pixel );
}
} // namespace
