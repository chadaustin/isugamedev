//////////////////////////////////////////////////////////////////////////////
//
//                         -=     BmpExport class     =-
//
// Description: "a class for loading of device independent bitmap (bmp) images"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: BmpExporter.cpp,v $
//    $Date: 2002-01-17 00:04:56 $
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
#include "Endian.h" // for bytereverse and littleEndian

#include "BmpExporter.h"
namespace pixmi
{
BmpExporter::BmpExporter() : ImageExporter()
{
   this->_init();
   this->addExtension( "bmp" );
}

//: a string that describes the files supported by this importer
const char* const BmpExporter::description() const
{
   return "Windows Bitmap Image";
}

//
// Destructor, free memory
//
BmpExporter::~BmpExporter()
{
   //Private to BmpExport...
   if( _bmiColors != NULL )
      delete _bmiColors;
}

//
// SaveFile --- loads a dib (device independent bitmap)
//
bool BmpExporter::save( const char* const filename, const Image& image )
{
   #ifdef WIN32
   ofstream hBitmapFile( filename, ios::out | ios::binary, filebuf::openprot );
   #else
   ofstream hBitmapFile( filename, ios::out, filebuf::openprot );
   #endif

   bmpheader::BITMAPFILEHEADER fileHeader;

   // bail if fileopen failed
   if( !hBitmapFile.rdbuf()->is_open() )
   {
      //Log<<"OOpS!: Can't write file\n"<<flush;
      hBitmapFile.close();
      this->_init();
      return false;
   }

   // calculate the (total) amount of additional row padding (in bytes) that will be added to the image data if alignment == 4.
   // This _really_ matters for _some_ paint programs (like gimp).  They somehow "determine" 
   // image attributes based on the bfSize and bfSizeImage fields.
   const int alignment = 4;
   //const int existingRowPaddingInImage = image.rowPadding() * image.height();
   const int neededRowPaddingForDestination = (image.width() % alignment) * image.height();
   //const int additionalRowPadding = neededRowPaddingForDestination - existingRowPaddingInImage;
   const int size_justRGB = image.width() * image.height() * 3 + neededRowPaddingForDestination;
   
   // make file-header from the image's data...
   // don't know why I have to subtract 2... go read the file spec and figure it out
   fileHeader.bfType = bmpheader::BMP_MAGIC;
   fileHeader.bfSize = size_justRGB + sizeof(bmpheader::BITMAPINFOHEADER) + sizeof(bmpheader::BITMAPFILEHEADER) - 2;
   fileHeader.bfReserved1 = 0;
   fileHeader.bfReserved2 = 0;
   fileHeader.bfOffBits = 54;
   
   //since BMP is little-endian native,
   // reverse the byte order when running on bigendian hardware.
   if (pixmi::isBigEndian())
   {
      pixmi::byteReverse(fileHeader.bfType );
      pixmi::byteReverse(fileHeader.bfSize );
      pixmi::byteReverse(fileHeader.bfReserved1 );
      pixmi::byteReverse(fileHeader.bfReserved2 );
      pixmi::byteReverse(fileHeader.bfOffBits );
   }
      
   // write file header
   hBitmapFile.write((char *)&fileHeader.bfType, sizeof(short)); //1,2
   hBitmapFile.write((char *)&fileHeader.bfSize, sizeof(long));  //3,4,5,6
   hBitmapFile.write((char *)&fileHeader.bfReserved1, sizeof(short)); //7,8
   hBitmapFile.write((char *)&fileHeader.bfReserved2, sizeof(short)); //9,10
   hBitmapFile.write((char *)&fileHeader.bfOffBits, sizeof(long)); //11,12,13,14
   
   //put the data back
   /*
   if (pixmi::isBigEndian())
   {
      pixmi::byteReverse(fileHeader.bfType );
      pixmi::byteReverse(fileHeader.bfSize );
      pixmi::byteReverse(fileHeader.bfReserved1 );
      pixmi::byteReverse(fileHeader.bfReserved2 );
      pixmi::byteReverse(fileHeader.bfOffBits );
   }
   */
   
   // make info-header from the image's data...
   _infoheader.biWidth = image.width();
   _infoheader.biHeight = image.height();
   _infoheader.biSizeImage = size_justRGB;
   _infoheader.biXPelsPerMeter = 1; //default
   _infoheader.biYPelsPerMeter = 1; //default

   //since BMP is little-endian native,
   // reverse the byte order when running on BigEndian hardware.
   if (pixmi::isBigEndian())
   {
      pixmi::byteReverse(_infoheader.biSize );
      pixmi::byteReverse(_infoheader.biWidth);
      pixmi::byteReverse(_infoheader.biHeight);
      pixmi::byteReverse(_infoheader.biPlanes);
      pixmi::byteReverse(_infoheader.biBitCount);
      pixmi::byteReverse(_infoheader.biCompression);
      pixmi::byteReverse(_infoheader.biSizeImage);
      pixmi::byteReverse(_infoheader.biXPelsPerMeter);
      pixmi::byteReverse(_infoheader.biYPelsPerMeter);
      pixmi::byteReverse(_infoheader.biClrUsed);
      pixmi::byteReverse(_infoheader.biClrImportant);
   }
   
   // write the info header.
   hBitmapFile.write((char *)&_infoheader.biSize , sizeof(unsigned long));//15,16,17,18
   hBitmapFile.write((char *)&_infoheader.biWidth, sizeof(unsigned long));//19,20,21,22
   hBitmapFile.write((char *)&_infoheader.biHeight, sizeof(unsigned long));//23,24,25,26
   hBitmapFile.write((char *)&_infoheader.biPlanes, sizeof(unsigned short));//27,28
   hBitmapFile.write((char *)&_infoheader.biBitCount, sizeof(unsigned short));//29,30
   hBitmapFile.write((char *)&_infoheader.biCompression, sizeof(unsigned long));//31,32,33,34
   hBitmapFile.write((char *)&_infoheader.biSizeImage, sizeof(unsigned long));//35,36,37,38
   hBitmapFile.write((char *)&_infoheader.biXPelsPerMeter, sizeof(unsigned long));//39,40,41,42
   hBitmapFile.write((char *)&_infoheader.biYPelsPerMeter, sizeof(unsigned long));
   hBitmapFile.write((char *)&_infoheader.biClrUsed, sizeof(unsigned long));;
   hBitmapFile.write((char *)&_infoheader.biClrImportant, sizeof(unsigned long));
   
   // put the bytes back...
   /*
   if (pixmi::isBigEndian())
   {
   pixmi::byteReverse(_infoheader.biSize );
   pixmi::byteReverse(_infoheader.biWidth);
   pixmi::byteReverse(_infoheader.biHeight);
   pixmi::byteReverse(_infoheader.biPlanes);
   pixmi::byteReverse(_infoheader.biBitCount);
   pixmi::byteReverse(_infoheader.biCompression);
   pixmi::byteReverse(_infoheader.biSizeImage);
   pixmi::byteReverse(_infoheader.biXPelsPerMeter);
   pixmi::byteReverse(_infoheader.biYPelsPerMeter);
   pixmi::byteReverse(_infoheader.biClrUsed);
   pixmi::byteReverse(_infoheader.biClrImportant);
   }
   */
   

   // allocate one (read ONE, 1 only!!) scanline for _use_ in writing the image (one scanline at a time).
   // we will save the image as 24bit, 3 channel
   // (im not alocating the alignment part here, i'll just write it later.)
   const int bpp = 24;
   const int channels = 3; 
   Image bgrImage;
   bgrImage.reserve( image.width(), 1, bpp, channels, alignment );

   // write the image.
   for (int k = 0; k < image.height(); ++k)
   {
      // prepare the scanline for copying
      const unsigned char* const rowSrc = image.row( k );
      unsigned char* rowDest = bgrImage.data();
      for (int t = 0; t < image.width(); ++t)
      {
         // an Image is naturally rgbrgbrgbrgb
         // we save the data as bgrbgrbgrbgr.
         // swap the b and r bytes
         // NOTE: this also handles dithering a 32 bit image to 24 bit.
         rowDest[t*3 + 0] = rowSrc[t*image.channels() + 2];
         rowDest[t*3 + 1] = rowSrc[t*image.channels() + 1];
         rowDest[t*3 + 2] = rowSrc[t*image.channels() + 0];
      }

      // Write next scan line, don't write any padding that might be there
      hBitmapFile.write( (unsigned char *)bgrImage.data(), image.width() * 3 );
      
      // align the image's bytes to 4-byte alignment.
      // in a BMP file, there will be [width]%4 amount of bytes padding in each row.
      int byte = 0x00000000;
      int padsize = bgrImage.width() % 4;
      hBitmapFile.write( (unsigned char *)&byte, padsize );
   }

   hBitmapFile.close();
   return true;
}

} // namespace
