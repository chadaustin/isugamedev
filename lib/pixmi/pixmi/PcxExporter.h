
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     PcxExport class     =-
//
// Description: "Exports a ZSoft PCX image.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PcxExporter.h,v $
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
#ifndef PCX_EXPORTER_INCLUDED
#define PCX_EXPORTER_INCLUDED

#include "PcxHeader.h"
#include "Image.h"
#include "ImageExporter.h"
#include "stdio.h"
namespace pixmi
{
//: PcxExporter
// Write an Image object out to file
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   /* now do some changes to the image, white noise, a fractal, etc.. */
//   PcxExporter pcx_export;
//   pcx_export( "bugs.pcx", image );
// 
// alternately, you can call operator() this way:
//   pcx_export.operator()( "bugs.pcx", image );
//
class PcxExporter : public ImageExporter
{   
public:
   //: Default constructor
   PcxExporter();      
      
   //: Destructor
   virtual ~PcxExporter();
      
   //: Save the image as "filename"
   //  returns true or false for successful or unsuccessful
   virtual bool            save( const char* const filename, const Image& image );

   //: a string that describes the files supported by this Exporter
   virtual const char* const   description() const;

private:
   

   


   //: Write the information from a PCX image file structure.
   //
   //  PCX header file information is read from the supplied PCX
   //  header structure and written to the supplied FILE stream.
   //  The ENDIANIO I/O finctions are used to insure that the header
   //  information is written in little-endian order.
   //
   //  Give:
   //  - PCX header structure
   //  - A writable binary FILE stream to write the header to.
   static void   WritePcxHeader( FILE* FpPcx, const PcxHeader& PcxHead );


   //: Encode (compress) a PCX image file scan line.
   //
   //  PcxEncodeScanLine() encodes a buffer containing raw scan line data
   //  using the PCX PackBytes run-length encoding algorithm.  The encoded
   //  data is written to a second buffer passed to the function.
   //
   //  The main problem when encoding a scan line is that we never know how
   //  long the resulting encoded scan line will be.  Typically it will be
   //  shorter than the unencoded line, however, this type of RLE encoding
   //  can make the resulting encoded data larger in size than the unencoded
   //  data depending upon the data being encoded.
   //
   //  It is therefore important that the buffer used to hold the encoded
   //  scan line be larger than what will typically be needed.  A size of
   //  2048 bytes should be more than plenty for typical VGA images.  The
   //  size of the buffer can be trimmed down to the size of the encoded
   //  data using realloc() and the return value of PcxEncodeScanLine()
   //  function, if necessary.
   //
   // NOTE: to encode PCX 24bit data, DecodedBuffer should consist of one channel of one scanline, 
   //       then, followed by the next two color planes, then the next scanline, etc...
   //       i.e.  rrrrrrrrrrrrrrrrrrrrrrrr <- first scanline
   //             gggggggggggggggggggggggg         .
   //             bbbbbbbbbbbbbbbbbbbbbbbb         .
   //             rrrrrrrrrrrrrrrrrrrrrrrr <- second scanline
   //             gggggggggggggggggggggggg         .
   //             bbbbbbbbbbbbbbbbbbbbbbbb         .
   // Give:
   //
   // DecodedBuffer - Source buffer (unencoded data)
   // BufferSize    - Size of DecodedBuffer in bytes
   // EncodedBuffer - Dest Buffer (encodeded scan line) 
   //
   // Returns: Number of bytes in compressed scan line.
   static unsigned short PcxEncodeScanLine( const unsigned char* const DecodedBuffer, 
                                   const unsigned short& BufferSize,
                                   unsigned char* EncodedBuffer );
};
} // namespace
#endif
