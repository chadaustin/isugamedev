#include <iostream>
#include <zlib.h>
#include "PngChunk.h"
#include "PngImporter.h"

using std::cout;
using std::flush;

namespace pixmi
{
//: Default constructor
PngImporter::PngImporter() 
{
   this->addExtension( "png" );
}
	
//: Destructor
PngImporter::~PngImporter()
{
}

void PngImporter::convertToImage( PngChunk& headerChunk, PngChunk& dataChunk, Image& image )
{
   int ret;

   assert( headerChunk.chunkType == IHDR && "not an IHDR type" );
   assert( dataChunk.chunkType == IDAT && "not an IDAT type" );

   // set up the image with info from the PNG header
   int channels( 3 );
   
   assert( headerChunk.compression_method() == 0 && "At present, only compression method 0 (deflate/inflate compression with a 32K sliding window) is defined" );
   assert( headerChunk.filter_type() == 0 && "At present, only filter method 0 (adaptive filtering with five basic filter types) is defined." );
   assert( headerChunk.interlace_method() == 0 && "only non-interlaced images are supported by this importer" );
   
   std::cout<<"  Width = "<<headerChunk.width()<<std::endl;
   std::cout<<"  Height = "<<headerChunk.height()<<std::endl;
   std::cout<<"  pixeldepth = "<<(int)headerChunk.pixel_depth()<<std::endl;
   std::cout<<"  color_type = "<<(int)headerChunk.color_type()<<std::endl;
   std::cout<<"  compression_method = "<<(int)headerChunk.compression_method()<<std::endl;
   std::cout<<"  filter_type = "<<(int)headerChunk.filter_type()<<std::endl;
   std::cout<<"  interlace_method = "<<(int)headerChunk.interlace_method()<<std::endl;

   if (headerChunk.color_type() == 2) // color(2)
      channels = 3;
   else if (headerChunk.color_type() == 6) // color(2) + alpha(4)
      channels = 4;
   else
      assert( false && "not implemented: reading of PNG colormaps (palettes)" );

   image.reserve( headerChunk.width(), headerChunk.height(), headerChunk.pixel_depth() * channels, channels, 1 );

   // initialize the zlib inflate utility
   // initialize zbuf - compression buffer
   z_stream zs;
   zs.zalloc = 0;
   zs.zfree = 0;
   zs.opaque = 0;
   switch (inflateInit(&zs))
   {
     case Z_OK: /* Do nothing */ break;
     case Z_MEM_ERROR:
     case Z_STREAM_ERROR: std::cout<<"  zlib memory error\n"<<std::flush; break;
     case Z_VERSION_ERROR: std::cout<<"  zlib version error"<<std::flush; break;
     default: std::cout<<"  Unknown zlib error\n"<<std::flush;
   }

   // length in bytes of one scanline + filter byte (which I ignore later)
   unsigned int irowbytes = ((image.width() * image.bpp() + 7) >> 3) + 1;
   
   // current row in the image to dump the uncompressed data to
   // go from top to bottom (0 is bottom)
   int nextrow = image.height();
   
   // space for one row.  first byte will be the filter type (im not doing filtering though...)
   std::vector<unsigned char> oneRow;
   oneRow.resize( irowbytes );
   
   zs.avail_in = dataChunk.chunkData.size();
   zs.next_in = &dataChunk.chunkData[0];
   
   zs.avail_out = irowbytes;
   zs.next_out = &oneRow[0];
   
   for(;;)
   {
      ret = inflate(&zs, Z_PARTIAL_FLUSH);
      if (ret != Z_OK)
      {
         if (ret == Z_STREAM_END)
         {
            if (zs.avail_in)
               std::cout<<"  Extra compressed data left\n"<<std::flush;
            if (!(zs.avail_out))
            {
               std::cout<<"Z_STREAM_END\n"<<std::flush;

               ////////////////////////////////////////////////////////////////
               // copy one row from the uncompressed data buffer to the image.
               std::cout<<"."<<std::flush;
               nextrow--;
               unsigned char* pixel = image.row( nextrow );
               for (int x = 0; x < image.width() * image.channels(); ++x)
               {
                  pixel[x] = oneRow[x+1];
               }
               ////////////////////////////////////////////////////////////////
            }

            break;
         }
         else if (ret == Z_BUF_ERROR)
            break;
         else
            std::cout<<"  Decompression Error retval="<<ret<<std::endl;
      }
      if (!(zs.avail_out))
      {
         ////////////////////////////////////////////////////////////////
         // copy one row from the uncompressed data buffer to the image.
         std::cout<<"."<<std::flush;
         nextrow--;
         unsigned char* pixel = image.row( nextrow );
         for (int x = 0; x < image.width() * image.channels(); ++x)
         {
            pixel[x] = oneRow[x+1];
         }
         ////////////////////////////////////////////////////////////////

         zs.avail_out = irowbytes;
         zs.next_out = &oneRow[0];
      }
      else
         break;
   }
   std::cout<<std::endl;

   
}

//: Save the image as "filename"
//  returns true or false for successful or unsuccessful
bool PngImporter::load( const char* const filename, Image& image )
{
   std::cout<<"reading png: \n"<<std::flush;

   image.setName( filename );
   
   FILE* fh = fopen( filename, "rb" );
   unsigned char buffer;
   for (int x = 0; x < 8; ++x)
   {
      CFileIO::ReadByte( fh, buffer );
      if (buffer != first8bytes[x])
      {
         std::cout<<"Header didn't match on byte "<<x<<" "<<(int)buffer<<"!="<<(int)first8bytes[x]<<std::endl;
         return false;
      }
   }
   std::cout<<"Header matched, "<<filename<<" is a PNG\n"<<std::flush;

   PngChunk pngChunk, pngData, pngHdr;

   do 
   {
      pngChunk.read( fh );
      switch (pngChunk.chunkType)
      {
      case IHDR:
         pngHdr = pngChunk;
         break;
      case IDAT:
         pngData = pngChunk;
         break;
      case IEND:
         break;
      }
   }
   while (pngChunk.chunkType != IEND && pngChunk.chunkType != 'DNEI' );

   this->convertToImage( pngHdr, pngData, image );

   return true;
}

//: a string that describes the files supported by this importer
const char* const	PngImporter::description() const { return "PNG (Portable Network Graphics)"; }
} // namespace
