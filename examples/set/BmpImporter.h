
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     BmpImport class     =-
//
// Description: "a class to load device independent bitmap (bmp) images"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: BmpImporter.h,v $
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
#ifndef _BITMAP_CLASS_
#define _BITMAP_CLASS_


#include "Image.h"
#include "BmpHeader.h"

namespace pixmi
{
//: BmpImporter
// Load an image file into an Image object
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   BmpImporter bmp_import;
//   bmp_import( "bugs.bmp", image );
// 
// alternately, you can call operator() this way:
//   bmp_import.operator()( "bugs.bmp", image );
//
class BmpImporter
{
public:
   BmpImporter();
   virtual ~BmpImporter();

   //: Load the file "filename"
   //  returns true or false for successful or unsuccessful
   //  returns an Image object
   virtual bool            load( const char* const filename, Image& image );

   //: a string that describes the files supported by this importer
   virtual const char* const   description() const;

private:
/*
   void            setWidth(const unsigned long& wide);
   const long&      getWidth() const;

   void                   setHeight(const unsigned long& high);
   const long&      getHeight() const;

   void               setPlanes(const unsigned short &planes);

   void               setBitCount(const unsigned short &count);
   const unsigned short&   getBitCount() const;

   void               setCompression(const unsigned long& com);
   const unsigned long&      getCompression() const;

   void               setSizeImage(const unsigned long& size)   ;
   const unsigned long&      getSizeImage() const;

   void               setXPelsPerMeter(const unsigned long& x);
   const long&      getXPelsPerMeter() const;
   void               setYPelsPerMeter(const unsigned long& y);
   const long&      getYPelsPerMeter()const;

   
   //return the number of color channels. (i.e. red,green,blue = 3)
   unsigned long         getChannels() const;
   
   //returns a 32 bit integer specifing number of colors
   //largest posible number returned is 2^32
   unsigned long         getColors()const;
   
   unsigned long         RowWidth()const;
   unsigned int         getBpp()const;
   void               getPaletteEntries(const int &first, 
                                 const int &count, 
                                 PALETTEENTRY *entries);
   */

protected:
   void                      _init();
   char *                      _imagename;
    bmpheader::BITMAPINFOHEADER      _infoheader;
   bmpheader::RGBQUAD          *   _bmiColors; 
};

//
// Init --- Initialize members
//
inline void BmpImporter::_init()
{
   //set some defaults...
   _infoheader.biSize          = sizeof(bmpheader::BITMAPINFOHEADER);
   _infoheader.biWidth         = 0; //320
   _infoheader.biHeight        = 0; //200
   _infoheader.biPlanes        = 1;
   _infoheader.biBitCount      = 24;
   _infoheader.biCompression   = 0;
   _infoheader.biSizeImage     = 0;
   _infoheader.biXPelsPerMeter = 2952;// 75 DPI 
   _infoheader.biYPelsPerMeter = 2952; // 75 DPI 
   _infoheader.biClrUsed       = 0;
   _infoheader.biClrImportant  = 0;
   _bmiColors = NULL;
}


/*
//
// ColorsUsed --- returns number of colors used by dib
//
inline unsigned long BmpImporter::getColors() const
{
   //assert( _info != NULL );
   //
   // If a color count is specified use it
   //
   //Look in BmpImport.h for more info on the data struct...
   if( _infoheader.biClrUsed != 0 )
      return _infoheader.biClrUsed;
   //
   // Else base number of colors on bits per pixel
   //
   switch( _infoheader.biBitCount )
   {
      case 1: 
         return (unsigned long)2;
      case 4: 
         return (unsigned long)0x0000000f + 1;
      case 8: 
         return (unsigned long)0x000000ff + 1;
      case 15:
         return (unsigned long)0x0000efff + 1;
      case 16: 
         return (unsigned long)0x0000ffff + 1;
      case 24:
         return (unsigned long)0x00ffffff + 1;
      case 32:
         return (unsigned long)0xffffffff;
      default: 
         return 0;
   }
}
//
// RowWidth --- returns the number of bytes in each row of pixels.
//
// note: this is always a multiple of 4
//
inline unsigned long BmpImporter::RowWidth() const
{
   long bitwidth;
   long bytewidth;

   //
   // Get width in pixels
   //
   bitwidth = this->getWidth() * this->getBitCount();
   //
   // Calculate width in bytes
   //
   bytewidth = (bitwidth + 7) >> 3;
   //
   // Return rounded value
   //
   return (bytewidth + 3) & -4;
}
//
// Bpp --- returns number of bits per pixel
//
inline unsigned int   BmpImporter::getBpp() const
{
//   assert( _info != NULL );

   return this->getBitCount();
}
//
// GetPaletteEntries --- returns a range of palette entries
//
// struct PALETTEENTRY is the same as struct RGBQUAD
inline void BmpImporter::getPaletteEntries(const int &first, const int &count, PALETTEENTRY * entries)
{
   memcpy(entries, &_bmiColors[first], count * sizeof(PALETTEENTRY) );
}

*/
      
      } // namespace

#endif
