//////////////////////////////////////////////////////////////////////////////
//
//                         -=     Bmp File Header Data     =-
//
// Description: "this file contains structures similar to the .bmp file header"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: BmpHeader.h,v $
//    $Date: 2002-04-24 07:20:05 $
//    $Revision: 1.1 $
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

#ifndef BMP_FILE_HEADER
#define BMP_FILE_HEADER

namespace pixmi
{
namespace bmpheader
{

   const short BMP_MAGIC = 'MB';

   // Bitmap Header Definition 
   // 32 bit
   struct BITMAP
   {
      unsigned long        bmType;
      unsigned long        bmWidth;
      unsigned long        bmHeight;
      unsigned long        bmWidthBytes;
      unsigned short       bmPlanes;
      unsigned short       bmBitsPixel;
      void        *bmBits;
   };

   //8 bit
   struct RGBTRIPLE 
   {
         unsigned  char    rgbtBlue;
         unsigned char    rgbtGreen;
         unsigned char    rgbtRed;
   };

   //8 bit
   struct RGBQUAD 
   {
         unsigned char    rgbBlue;
         unsigned char    rgbGreen;
         unsigned char    rgbRed;
         unsigned char    rgbReserved;
   };
   
   struct BITMAPINFOHEADER
   { 
      unsigned long      biSize; 
      long               biWidth;
      long               biHeight;
      unsigned short      biPlanes;      //16 bit
      unsigned short      biBitCount; 
      unsigned long      biCompression;   //32bit
      unsigned long      biSizeImage;
      long               biXPelsPerMeter; 
      long               biYPelsPerMeter; 
      unsigned long      biClrUsed;
      unsigned long      biClrImportant; 
   };

   struct BITMAPINFO 
   { 
      BITMAPINFOHEADER bmiHeader; 
      RGBQUAD          bmiColors[1]; 
   };

   struct BITMAPFILEHEADER 
   {
      unsigned short      bfType; 
      unsigned long      bfSize;
      unsigned short      bfReserved1; 
      unsigned short      bfReserved2;
      unsigned long      bfOffBits;
   }; 

   struct BITMAPCOREHEADER 
   {
      unsigned long      bcSize;                 // used to get to color table
      unsigned short      bcWidth;
      unsigned short      bcHeight;
      unsigned short      bcPlanes;
      unsigned short      bcBitCount;
   };

   struct BITMAPCOREINFO 
   {
      BITMAPCOREHEADER    bmciHeader;
      RGBTRIPLE           bmciColors[1];
   };

   //constants for the biCompression field
   enum BiCompressionFieldConstant
   {
		BII_RGB        = 0,
		BII_RLE8       = 1,
		BII_RLE4       = 2,
		BII_BITFIELDS  = 3
   };

   struct PALETTEENTRY 
   { 
      unsigned char peRed;     
      unsigned char peGreen; 
      unsigned char peBlue;
      unsigned char peFlags; 
   };





   struct CIEXYZ
   {
      unsigned long ciexyzX;     
      unsigned long ciexyzY;    
      unsigned long ciexyzZ; 
   }; 

   struct CIEXYZTRIPLE
   {
      CIEXYZ  ciexyzRed;     
      CIEXYZ  ciexyzGreen;     
      CIEXYZ  ciexyzBlue; 
   };

   struct BITMAPV4HEADER
   {
         unsigned long        bV4Size;
         unsigned long        bV4Width;
         unsigned long        bV4Height;
         unsigned short       bV4Planes;
         unsigned short       bV4BitCount;
         unsigned long        bV4V4Compression;
         unsigned long        bV4SizeImage;
         unsigned long        bV4XPelsPerMeter;
         unsigned long        bV4YPelsPerMeter;
         unsigned long        bV4ClrUsed;
         unsigned long        bV4ClrImportant;
         unsigned long        bV4RedMask;
         unsigned long        bV4GreenMask;
         unsigned long        bV4BlueMask;
         unsigned long        bV4AlphaMask;
         unsigned long        bV4CSType;
         CIEXYZTRIPLE       bV4Endpoints;
         unsigned long        bV4GammaRed;
         unsigned long        bV4GammaGreen;
         unsigned long        bV4GammaBlue;
   };
};
} // namespace
#endif
