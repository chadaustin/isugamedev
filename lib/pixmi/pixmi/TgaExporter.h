
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     TgaExport class     =-
//
// Description: "Exporter for Targa files.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: TgaExporter.h,v $
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
#ifndef TGA_EXPORTER_INCLUDED
#define TGA_EXPORTER_INCLUDED

#include "Image.h"
#include "ImageExporter.h"
namespace pixmi
{
//: TgaExporter
// Write an Image object out to file
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   /* now do some changes to the image, white noise, a fractal, etc.. */
//   TgaExporter tga_export;
//   tga_export( "bugs.tga", image );
// 
// alternately, you can call operator() this way:
//   tga_export.operator()( "bugs.tga", image );
//
class TgaExporter : public ImageExporter
{   
public:
   //: Default constructor
   TgaExporter();      
      
   //: Destructor
   virtual ~TgaExporter();
      
   //: Save the image as "filename"
   //  returns true or false for successful or unsuccessful
   virtual bool            save( const char* const filename, const Image& image );   
   
   //: a string that describes the files supported by this importer
   virtual const char* const   description() const;
private:
   
   //: Encode one scanline of data.
   //  does compression using pixel by pixel RLE encoding
   //
   // unencodedBuffer - Source buffer (unencoded data)
   // BufferSize    - Size of the source unencodedBuffer in bytes
   // bpp           - pixel depth, usually one of 8, 16, 24, 32
   // EncodedBuffer - Dest Buffer (encodeded scan line) 
   //
   // Returns: Number of bytes in compressed scan line.
   static int               RLEncodeRow(const unsigned char* unencodedBuffer,
                                  int BufferSize,
                                  int bpp,
                                  unsigned char* encodedBuffer );

   // Count pixels in buffer until two identical adjacent ones found
   static int               CountDiffPixels( const unsigned char* p,
                                    int bpp,
                                    int pixCnt );

   static int               CountSamePixels( const unsigned char* p,
                                    int bpp,
                                    int pixCnt );

   // Retrieve a pixel value from a buffer.  The actual size and order
   // of the bytes is not important since we are only using the value
   // for comparisons with other pixels.
   static unsigned long      GetPixel( const unsigned char* p, int bpp );
};

} // namespace
#endif
