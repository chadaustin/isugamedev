
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     TgaImport class     =-
//
// Description: "Importer for Targa files.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: TgaImporter.cpp,v $
//    $Date: 2002-01-17 00:04:58 $
//    $Revision: 1.1.1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
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

#include <iostream>
#include <assert.h>
#include <string>         // for std::string
#include "Defines.h"      // needed for pixmi::byteReverse()
#include "CFileIO.h"      // needed to write out binary data with proper endianness.
#include "TgaHeader.h"         // the TGA header data structure
#include "Endian.h" // for bytereverse and littleEndian

#include "TgaImporter.h"

namespace pixmi
{

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


//: Default constructor
TgaImporter::TgaImporter()
{
   this->addExtension( "tga" );
   this->addExtension( "vda" );
   this->addExtension( "icb" );
   this->addExtension( "vst" );
   this->addExtension( "win" );
}

//: Destructor
TgaImporter::~TgaImporter()
{
}

// (this was fun to write.)
// data       - pointer to buffer to recieve uncompressed data.
// bufferSize - buffer size in bytes
// bpp        - bytes per pixel (8, 16, 24, 32)
// fp         - file pointer, must be an opened file, ::use fseek to position at valid start of RLE row.
int TgaImporter::ReadRLERow( unsigned char* data, const int& bufferSize, const int& bpp, FILE *fp )
{
   unsigned int   value;  
   unsigned char   byte;   // for reading byte by byte.
   int      i;
   unsigned char*   q;
   int      n( bufferSize );
   static unsigned char rleBuf[RLEBUFSIZ];
      
   while ( n > 0 )
   {
      CFileIO::ReadByte( fp, byte );
      value = byte;

      if ( value & 0x80 )
      {
         value &= 0x7f;
         value++;
         n -= value * bpp;
         if ( n < 0 ) 
            return( -1 );
         if ( ::fread( rleBuf, 1, bpp, fp ) != bpp ) return( -1 );
         while ( value > 0 )
         {
            *data++ = rleBuf[0];
            if ( bpp > 1 ) *data++ = rleBuf[1];
            if ( bpp > 2 ) *data++ = rleBuf[2];
            if ( bpp > 3 ) *data++ = rleBuf[3];
            value--;
         }
      }
      else
      {
         value++;
         n -= value * bpp;
         if ( n < 0 ) 
            return( -1 );
         
         // Maximum for value is 128 so as long as RLEBUFSIZ
         // is at least 512, and bpp is not greater than 4
         // we can read in the entire raw packet with one operation.
         if ( fread( rleBuf, bpp, value, fp ) != value ) 
            return( -1 );
         for ( i = 0, q = rleBuf; i < (value * bpp); ++i ) *data++ = *q++;
      }
   }
   return( 0 );
}

//: Save the image as "filename"
//  returns true or false for successful or unsuccessful
bool TgaImporter::load( const char* const filename, Image& image )
{
   if (!CFileIO::fileExists( filename ))
   {
      std::cout<<"File doesn't exist!\n"<<std::flush;
      return false;
   }

   //if tga, then we need to load it
   // Open the file.
   TGAHeader header;
   FILE* fp = ::fopen( filename, "rb" );
   assert( fp != NULL && "CFileIO::fileExists passed, but fopen did not" );

   // It would be nice to be able to read in the entire structure with one fread, but hardware dependent
   // structure alignment precludes the simplistic approach. Instead, fill each field individually, 
   // and use routines that will allow code to execute on various hosts by recompilation with particular 
   // compiler flags.
   //
   // Start by reading the fields associated with the original TGA format.
   CFileIO::ReadByte( fp, header.idLength );
   CFileIO::ReadByte( fp, header.mapType );
   CFileIO::ReadByte( fp, header.imageType );
   CFileIO::ReadShort( CFileIO::LITTLE, fp, header.mapStart );
   CFileIO::ReadShort( CFileIO::LITTLE, fp, header.mapLength );
   CFileIO::ReadByte( fp, header.mapDepth );
   CFileIO::ReadShort( CFileIO::LITTLE, fp, header.xOrigin );
   CFileIO::ReadShort( CFileIO::LITTLE, fp, header.yOrigin );
   CFileIO::ReadShort( CFileIO::LITTLE, fp, header.imageWidth );
   CFileIO::ReadShort( CFileIO::LITTLE, fp, header.imageHeight );
   //std::cout<<header.xOrigin<<","<<header.yOrigin <<" "<<header.imageWidth<<","<<header.imageHeight<<"\n"<<std::flush;
   CFileIO::ReadByte( fp, header.pixelDepth );
   CFileIO::ReadByte( fp, header.imageDesc );
   //std::cout<<"Image Desc: "<<(int)header.imageDesc<<"\n"<<std::flush;

   //: currently only 8 and 24 and 32 bit is supported
   if (header.pixelDepth != 8 && header.pixelDepth != 24 && header.pixelDepth != 32)
   {
      pixmi::Alert( false, "Importer only supports 24 and 32bit TGA." );   
      return false;
   }

   //: header.imageType = ???  (* == supported)
   //   ImageType   Datatype      Colormap   Encoding
   //   0         no image data   n         n
   //   1         colormapped      y         n
   // * 2         truecolor      n         n
   // * 3         monochrome      n         n
   //   9         colormapped      y         y
   // * 10         truecolor      n         y
   //   11         monochrome      n         y
   
   //: currently only truecolor or monochrome (compressed, and uncompressed) is supported
   if (header.imageType != 3 && header.imageType != 11 && //monochrome
      header.imageType != 2 && header.imageType != 10)   //truecolor
   {
      std::cout<<"Only support Truecolor (24 and 32bit) and monochrome (8bit) TGA's\n"<<std::flush;
      return false;
   }

   // TODO: useless?
   /*
   //: read the image id string.
   ::memset( header.idString, 0, 256 );
   if ( header.idLength > 0 ) 
   {
      // read the string
      // NOTE: as long as idLength is char, it wont overflow the buffer.
      char* imageIdString = reinterpret_cast<char*>(header.idString);
      ::fread( imageIdString, sizeof(char), header.idLength, fp );
   }
   */

   // Extended header stuff
   /*
   // Seek to the end of the file
   // there may be 2 longs, and an 18 char string there. (26 bytes total)
   int xTgaFormat = 0;
   if ( ::fseek( fp, -26, SEEK_END ) != 0 ) 
   {
      pixmi::Alert( false && "Error seeking to end of file for possible extension data." );
      return false;
   }

   // Read the first two longs (8 bytes)
   // get the offset to the xtended header (if it exists)
   header.extAreaOffset = CFileIO::ReadLong( CFileIO::LITTLE, fp );
   header.devDirOffset = CFileIO::ReadLong( CFileIO::LITTLE, fp );
   
   // Read the signature (18 bytes)
   // compare it to see if the file is the new (extended) TGA format.
   ::fgets( header.signature, 18, fp );
   if (std::string( "TRUEVISION-XFILE." ) == header.signature)
      xTgaFormat = 1;
   else 
   {
      // Reset offset values since this is not a new TGA file
      header.extAreaOffset = 0L;
      header.devDirOffset = 0L;
   }

   //: if it's an extended TGA file, then read the extended header.
   if ( xTgaFormat && header.extAreaOffset )
   {
      if ( ReadExtendedTGA( fp, &header ) < 0 ) 
         return false;
   }
   */

   // initialize the Image
   int bytesPerPixel = (header.pixelDepth + 7) >> 3;
   image.free();
   image.setName( filename );
   image.reserve( header.imageWidth - header.xOrigin, header.imageHeight - header.yOrigin, header.pixelDepth, bytesPerPixel );

   // figure out stats for the colormap info (if any), we'll need the length so we can find the pixel area.
   int colorMapLength = 0;
   if (header.mapType == 1)
   {
      int bytesPerPaletteElement = (header.mapDepth + 7) >> 3;
      colorMapLength = bytesPerPaletteElement * header.mapLength;
   }

   // Truecolor data starts sizeof(TGAOriginalHeader) from beginning. (18)
   // This is true for both RLE and uncompressed scanlines.
   int dataAreaOffset = 18 + header.idLength + colorMapLength;
   if ( ::fseek( fp, dataAreaOffset, SEEK_SET ) != 0 )
   {
      pixmi::Alert( false, "Couldn't seek within the file to the image data portion" );
      return false;
   }

   //is the image stored upside down?
   bool isUpsideDown = ((header.imageDesc & (0x01<<5)) == (0x01<<5));

   //is the image stored flipped?
   bool isHorzFlipped = ((header.imageDesc & (0x01<<4)) == (0x01<<4));

   //: Read Image Data --> truecolor/monochrome and compressed (easy)
   if ( header.imageType == 10 || header.imageType == 11 )
   {
      // allocate data to uncompress a scanline.
      int bCount = header.imageWidth * bytesPerPixel;

      //: process each scanline one by one.
      for ( int i = 0; i < header.imageHeight; ++i )
      {         
         int j = i;   
         if (isUpsideDown)
         {
            j = header.imageHeight - i - 1;
         }

         //: expand one scanline of RLE data from the file...
         if (ReadRLERow( image.row( j ), bCount, bytesPerPixel, fp ) < 0)
         {
            // Indicate an error, but return true so that the user can at least see what is in the image
            // TODO: there may be times when the user will want this to fail, such as a texture loader 
            //       in a professional-grade simulation where you want to ensure your client wont see crap.
            pixmi::Alert( false, "Error decompressing RLE data." );
            //return true;
         }
      
         if (isHorzFlipped)
         {
            image.flipRow( j );
         }         
      }
   }

   //: Read Image Data --> truecolor/monochrome and UNcompressed
   else if ( header.imageType == 2 || header.imageType == 3 )
   {
      int rowStart, columnStart;
      int onePixelSize = image.channels();
      
      // Which row do we start at?
      // NOTE: this depends on if the image is upside down
      if ( isUpsideDown )
      {
         std::cout<<"Upside Down, reading backwards:\n"<<std::flush;
         rowStart = image.height() - 1;
      }
      
      else
      {
         rowStart = 0;
      }
         
      // Where is the beginning of one row?
      // NOTE: this depends on if the image is flipped or not
      if ( isHorzFlipped )
      {
         std::cout<<"Horz Flipped, reading backwards:\n"<<std::flush;
         columnStart = image.width() - 1;
      }
      
      else
      {
         columnStart = 0;
      }
      
      // Read the image in the correct order.
      // NOTE: y and x are just counters. 
      //       i and j actually traverse the image.
      int j = rowStart;
      for ( int y = 0; y < image.height(); ++y )
      {
         int i = columnStart;   
         for ( int x = 0; x < image.width(); ++x )
         {
            
            //: expand one scanline of RLE data from the file...
            if (::fread( image.pixel(i, j), sizeof(unsigned char), onePixelSize, fp ) != onePixelSize)
            {
               // Indicate an error, but return true so that the user can at least see what is in the image
               // TODO: there may be times when the user will want this to fail, such as a texture loader 
               //       in a professional-grade simulation where you want to ensure your client wont see crap.
               pixmi::Alert( false, "Error reading image data." );
               return true;
            }
            
            //std::cout<<i<<std::flush;
            if (isHorzFlipped) 
               --i;
            else
               ++i;
         }
         
         //std::cout<<":"<<j<<":\n"<<std::flush;
         if (isUpsideDown) 
            --j;
         else
            ++j;
      }
   }

   // swap the Red and Blue channels, BGRA -> RGBA, or BGR -> RGB
   // NOTE: only do this if there is a red and blue channel.
   if (header.pixelDepth == 24 || header.pixelDepth == 32)
      image.swapChannels(0,2);

   // done with file, close it.
   assert( fp != NULL && "File pointer is NULL, right after using it? (Makes no sense)" );
   ::fclose( fp );

   return true;
}

//: a string that describes the files supported by this importer
const char* const TgaImporter::description() const
{
   return "Truevision Graphics Adapter";
}



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Not needed yet. ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

/*

void ReadCharField( FILE   *fp,
               char   *p,
               int      n )
{
   assert( p != NULL && "ReadCharField recieved a NULL ptr." );
   while ( n )
   {
      *p++ = (char)fgetc( fp );   // no error check, no char conversion
      --n;
   }
}

int ReadColorTable( FILE   *fp,
               TGAFile   *sp )
{
   unsigned short   *p;
   unsigned short   n;

   if ( !fseek( fp, sp->colorCorrectOffset, SEEK_SET ) )
   {
      void* newMem = malloc( 1024 * sizeof( unsigned short ) );
      if ( newMem )
      {
         sp->colorCorrectTable = reinterpret_cast<unsigned short*>(newMem);
         p = sp->colorCorrectTable;
         for ( n = 0; n < 1024; ++n )
         {
            *p++ = CFileIO::ReadShort( CFileIO::LITTLE, fp );
         }
      }
      else
      {
         puts( "Unable to allocate Color Correction Table." );
         return( -1 );
      }
   }
   else
   {
      printf( "Error seeking to Color Correction Table, offset = 0x%08lx\n",
         sp->colorCorrectOffset );
      return( -1 );
   }
   return( 0 );
}

int ReadScanLineTable( FILE   *fp, TGAFile *sp )

{
   unsigned long   *p;
   unsigned short   n;

   if ( !fseek( fp, sp->scanLineOffset, SEEK_SET ) )
   {
      void* newMem = malloc( sp->imageHeight << 2 );
      if ( newMem )
      {
         sp->scanLineTable = reinterpret_cast<unsigned long*>(newMem);
         p = sp->scanLineTable;
         for ( n = 0; n < sp->imageHeight; ++n )
         {
            *p++ = CFileIO::ReadShort( CFileIO::LITTLE, fp );
         }
      }
      else
      {
         puts( "Unable to allocate Scan Line Table." );
         return( -1 );
      }
   }
   else
   {
      printf( "Error seeking to Scan Line Table, offset = 0x%08lx\n",
         sp->scanLineOffset );
      return( -1 );
   }
   return( 0 );
}

int ReadExtendedTGA( FILE* fp, TGAFile* sp )
{
   if ( !fseek( fp, sp->extAreaOffset, SEEK_SET ) )
   {
      sp->extSize = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      memset( sp->author, 0, 41 );
      ReadCharField( fp, sp->author, 41 );
      memset( &sp->authorCom[0][0], 0, 81 );
      ReadCharField( fp, &sp->authorCom[0][0], 81 );
      memset( &sp->authorCom[1][0], 0, 81 );
      ReadCharField( fp, &sp->authorCom[1][0], 81 );
      memset( &sp->authorCom[2][0], 0, 81 );
      ReadCharField( fp, &sp->authorCom[2][0], 81 );
      memset( &sp->authorCom[3][0], 0, 81 );
      ReadCharField( fp, &sp->authorCom[3][0], 81 );

      sp->month = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->day = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->year = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->hour = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->minute = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->second = CFileIO::ReadShort( CFileIO::LITTLE, fp );

      memset( sp->jobID, 0, 41 );
      ReadCharField( fp, sp->jobID, 41 );
      sp->jobHours = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->jobMinutes = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->jobSeconds = CFileIO::ReadShort( CFileIO::LITTLE, fp );

      memset( sp->softID, 0, 41 );
      ReadCharField( fp, sp->softID, 41 );
      sp->versionNum = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->versionLet = CFileIO::ReadByte( fp );

      sp->keyColor = CFileIO::ReadLong( CFileIO::LITTLE, fp );
      sp->pixNumerator = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->pixDenominator = CFileIO::ReadShort( CFileIO::LITTLE, fp );

      sp->gammaNumerator = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      sp->gammaDenominator = CFileIO::ReadShort( CFileIO::LITTLE, fp );

      sp->colorCorrectOffset = CFileIO::ReadLong( CFileIO::LITTLE, fp );
      sp->stampOffset = CFileIO::ReadLong( CFileIO::LITTLE, fp );
      sp->scanLineOffset = CFileIO::ReadLong( CFileIO::LITTLE, fp );

      sp->alphaAttribute = CFileIO::ReadByte( fp );

      sp->colorCorrectTable = NULL;
      if ( sp->colorCorrectOffset )
      {
         ReadColorTable( fp, sp );
      }

      sp->postStamp = NULL;
      if ( sp->stampOffset )
      {
         if ( !fseek( fp, sp->stampOffset, SEEK_SET ) )
         {
            sp->stampWidth = CFileIO::ReadByte( fp );
            sp->stampHeight = CFileIO::ReadByte( fp );

            // Leave the processing of postage stamp data to
            // the output phase of the program.  All we really
            // need to know is whether it exists in the input file.
         }
         else
         {
            printf( "Error seeking to Postage Stamp, offset = 0x%08lx\n",
               sp->stampOffset );
         }
      }

      sp->scanLineTable = (unsigned long *)0;
      if ( sp->scanLineOffset )
      {
         ReadScanLineTable( fp, sp );
      }
   }
   else
   {
      printf( "Error seeking to Extended TGA Area, offset = 0x%08lx\n", sp->extAreaOffset );
      return( -1 );
   }
   return( 0 );
}
int ReadDeveloperDirectory( FILE   *fp,
                     TGAFile   *sp )
{
   int            i;

   if ( !fseek( fp, sp->devDirOffset, SEEK_SET ) )
   {
      sp->devTags = CFileIO::ReadShort( CFileIO::LITTLE, fp );
      void* newMem = malloc( sp->devTags * sizeof(DevDir) );
      if ( newMem == NULL )
      {
         puts( "Unable to allocate developer directory." );
         return( -1 );
      } 
      sp->devDirs = reinterpret_cast<DevDir*>(newMem);
      for ( i = 0; i < sp->devTags; ++i )
      {
         sp->devDirs[i].tagValue = CFileIO::ReadShort( CFileIO::LITTLE, fp );
         sp->devDirs[i].tagOffset = CFileIO::ReadLong( CFileIO::LITTLE, fp );
         sp->devDirs[i].tagSize = CFileIO::ReadLong( CFileIO::LITTLE, fp );
      }
   }
   else
   {
      printf( "Error seeking to Developer Area at offset 0x%08lx\n",
         sp->devDirOffset );
      return(-1);
   }
   return( 0 );
}


*/

} // namespace
