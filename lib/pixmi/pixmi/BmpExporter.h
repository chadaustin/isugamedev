//////////////////////////////////////////////////////////////////////////////
//
//                         -=     BmpExport class     =-
//
// Description: "a class to load device independent bitmap (bmp) images"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: BmpExporter.h,v $
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
#ifndef _BITMAP_EXPORT_CLASS_
#define _BITMAP_EXPORT_CLASS_

#include "Image.h"
#include "BmpHeader.h"
#include "ImageExporter.h"

namespace pixmi
{
   
   //: BmpExporter
   // Write an Image object out to file
   //
   // To use, declare an instance of this class,
   // then call operator() with the filename and Image object you wish to act on.
   // i.e:
   //   Image image;
   //   /* now do some changes to the image, white noise, a fractal, etc.. */
   //   BmpExporter bmp_export;
   //   bmp_export( "bugs.bmp", image );
   // 
   // alternately, you can call operator() this way:
   //   bmp_export.operator()( "bugs.bmp", image );
   //
   class BmpExporter : public ImageExporter
   {
   public:
      BmpExporter();
      virtual ~BmpExporter();

      //: Load the file "filename"
      //  returns true or false for successful or unsuccessful
      //  returns an Image object
      virtual bool      save( const char* const filename, const Image& image );

      //: a string that describes the files supported by this importer
      virtual const char* const   description() const;

   private:
      void                        _init();
      char *                      _imagename;
      bmpheader::BITMAPINFOHEADER _infoheader;
      bmpheader::RGBQUAD*         _bmiColors; 
   };

   //
   // Init --- Initialize members
   //
   inline void BmpExporter::_init()
   {
      //set some defaults...
      _infoheader.biSize          = sizeof(bmpheader::BITMAPINFOHEADER);
      _infoheader.biWidth         = 0; //320
      _infoheader.biHeight        = 0; //200
      _infoheader.biPlanes        = 1;
      _infoheader.biBitCount      = 24;
      _infoheader.biCompression   = bmpheader::BI_RGB;
      _infoheader.biSizeImage     = 0;
      _infoheader.biXPelsPerMeter = 2952;// 75 DPI 
      _infoheader.biYPelsPerMeter = 2952; // 75 DPI 
      _infoheader.biClrUsed       = 0;
      _infoheader.biClrImportant  = 0;
      _bmiColors = NULL;
   }

} // namespace

#endif
