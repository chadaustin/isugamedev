
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     PcxExport class     =-
//
// Description: "Exports a ZSoft PCX image.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: PcxExporter.cpp,v $
//    $Date: 2002-01-17 00:04:57 $
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
#include "Defines.h"      // needed for pixmi::byteReverse()
#include "CFileIO.h"      // needed to write out binary data with proper endianness.

#include "PcxExporter.h"   // my header


//////////////////////////////////////////////
///  Public Members:
/////////////////////////////////////////////
namespace pixmi
{
//: Default constructor
PcxExporter::PcxExporter() : ImageExporter()
{
   this->addExtension( "pcx" );
}

//: Destructor
PcxExporter::~PcxExporter()
{
}

//: a string that describes the files supported by this Exporter
const char* const PcxExporter::description() const
{
   return "ZSoft PCX Image";
}

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
void PcxExporter::WritePcxHeader( FILE* FpPcx, const PcxHeader& PcxHead )
{
    CFileIO::WriteByte( FpPcx, PcxHead.Id );
    CFileIO::WriteByte( FpPcx, PcxHead.Version );
    CFileIO::WriteByte( FpPcx, PcxHead.Format );
    CFileIO::WriteByte( FpPcx, PcxHead.BitsPixelPlane );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.Xmin );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.Ymin );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.Xmax );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.Ymax );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.Hdpi );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.Vdpi );

    // Write the EGA Palette 
   register short i;
   for (i = 0; i < sizeof(PcxHead.EgaPalette); i++)
        CFileIO::WriteByte( FpPcx, PcxHead.EgaPalette[i] );

    CFileIO::WriteByte( FpPcx, PcxHead.Reserved );       
    CFileIO::WriteByte( FpPcx, PcxHead.NumberOfPlanes );
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.charsLinePlane ); 
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.PaletteInfo );  
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.HScreenSize );  
    CFileIO::WriteShort( CFileIO::LITTLE, FpPcx, PcxHead.VScreenSize );

    // Write the reserved area at the end of the header 
    for (i = 0; i < sizeof(PcxHead.Filler); i++)
        CFileIO::WriteByte( FpPcx, PcxHead.Filler[i] );
}

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
unsigned short PcxExporter::PcxEncodeScanLine( const unsigned char* const DecodedBuffer, 
                                   const unsigned short& BufferSize,
                                   unsigned char* EncodedBuffer )
{
    register unsigned short index = 0;        // Index into uncompressed data buffer  
    register unsigned short scanindex = 0;    // Index into compressed data buffer    
    unsigned char runcount;                   // Length of encoded pixel run          
    unsigned char runvalue;                   // Value of encoded pixel run           

    while (index < BufferSize)
    {
        // Get the run count of the next pixel value run.
        //
        // Pixel value runs are encoded until a different pixel value
        // is encountered, the end of the scan line is reached, or 63
        // pixel values have been counted.
        for (runcount = 1, runvalue = DecodedBuffer[index];
             runvalue == DecodedBuffer[index + runcount] &&
             index + runcount < BufferSize &&
             runcount < 63;
             runcount++);

        // Encode the run into a one or two-byte code.
        //
        // Multiple pixel runs are stored in two-byte codes.  If a single
        // pixel run has a value of less than 64 then it is stored in a
        // one-byte code.  If a single pixel run has a value of 64 to 255
        // then it is stored in a two-byte code.
        if (runcount > 1)                   // Multiple pixel run 
        {
            EncodedBuffer[scanindex++] = runcount | 0xC0;
            EncodedBuffer[scanindex++] = runvalue;       
        }
        else                                // Single pixel run   
        {
            if (DecodedBuffer[index] < 64)  // Value is 0 to 63   
            {
                EncodedBuffer[scanindex++] = runvalue;
            }
            else                            // Value is 64 to 255 
            {
                EncodedBuffer[scanindex++] = runcount | 0xC0;
                EncodedBuffer[scanindex++] = runvalue;       
            }
        }
        index += runcount;  // Jump ahead to next pixel run value 
    }
    return scanindex;      // Return the number of bytes written to buffer 
}

//: Save the image as "filename"
//  returns true or false for successful or unsuccessful
bool PcxExporter::save( const char* const filename, const Image& image )
{
   //: Open a file to write as binary.
   PcxHeader header;
   FILE* fp = ::fopen( filename, "wb" );
   if (fp == NULL)
   {
      pixmi::Alert( fp != NULL, "Could not open file for writing" );
      return false;
   }

   //: fill out the PCX header
   header.Id = 0x0A;
   header.Version = 5;         // this indicates 24 bit / Version 3.0 PC Paintbrush image.
   header.Format = 1;         // the encoding ID must be 1 (for RLE), this is the only supported data format in PCX.
   header.BitsPixelPlane = 8;   // 8 bit color planes
   header.Xmin = 0;
   header.Ymin = 0;
   header.Xmax = image.width() - 1;
   header.Ymax = image.height() - 1;
   header.Hdpi = 0;
   header.Vdpi = 0;

   header.Reserved = 0;      // This has to be 0

   header.NumberOfPlanes = 3;   //image.channels();
   header.charsLinePlane = image.width();
   header.PaletteInfo = 0;      // TODO: does this matter?
   header.HScreenSize = 0;  
   header.VScreenSize = 0;
   ::memset( &header.Filler, 0, sizeof(header.Filler) );

   //: output the PCX header info to file.
   PcxExporter::WritePcxHeader( fp, header );

   //: allocate plenty of data for one encoded scanline
   unsigned char* encodedBuffer = new unsigned char[image.width() * image.channels() * 2];
   unsigned char* oneScanlinePlane = new unsigned char[image.width()];

   //: for each scanline...
   for (int i = image.height() - 1; i >= 0; --i)
   {
      //: encode then write red, encode then write green, encode then write blue.
      //  This will skip the alpha channel if there is one, since it only encodes 3 channels. (PCX only supports 24bit)
      for (int channel = 0; channel < 3; ++channel)
      {
         //: copy from the image: one scanline's colorplane 
         //  i.e. copy all the red pixels from current row into "oneScanlinePlane"
         const unsigned char* const rowPtr = image.row(i);
         for (int j = 0; j < image.width(); ++j)
         {
            int kde = channel + j*image.channels();
            oneScanlinePlane[j] = rowPtr[kde];
         }

         //: encode the scanline's colorplane
         int scanLineSize = PcxExporter::PcxEncodeScanLine( oneScanlinePlane, image.width(), encodedBuffer );
      
         //: Write encoded scanline to output FILE stream
         if (scanLineSize != ::fwrite( encodedBuffer, sizeof(unsigned char), scanLineSize, fp ))
         {
            pixmi::Alert( false, "Couldn't write all image data" );
            return false;
         }
      }
   }

   delete[] oneScanlinePlane;
   delete[] encodedBuffer;

   //: close the file
   ::fclose( fp );

   //: success! (what else is there?)
   return true;
}

} // namespace
