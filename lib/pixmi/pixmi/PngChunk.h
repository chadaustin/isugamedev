#ifndef PNG_CHUNK
#define PNG_CHUNK

#include <CFileIO.h>
#include <iostream>
#include "PngCRC.h"
#include <string>
#include <vector>
#include <assert.h>


namespace pixmi
{
   
const unsigned char first8bytes[8] = {137, 80, 78, 71, 13, 10, 26, 10};

const unsigned long IHDR = 'IHDR';
// Width:              4 bytes (signed)
// Height:             4 bytes
// Bit depth:          1 byte   // valid: 1, 2, 4, 8, and 16
// Color type:         1 byte   // Color type codes represent sums of the following values: 
                                // 1 (palette used), 2 (color used), and 4 (alpha channel used). 
                                // Valid values are 0, 2, 3, 4, and 6
// Compression method: 1 byte   // At present, only compression method 0 
                                // (deflate/inflate compression with a 32K sliding window) is defined. 
// Filter method:      1 byte   // At present, only filter method 0 (adaptive filtering with five basic filter types) is defined. 
// Interlace method:   1 byte   // Two values are currently defined: 0 (no interlace) or 1 (Adam7 interlace). 
/*
   Color    Allowed    Interpretation
   Type    Bit Depths
   
   0       1,2,4,8,16  Each pixel is a grayscale sample.
   
   2       8,16        Each pixel is an R,G,B triple.
   
   3       1,2,4,8     Each pixel is a palette index;
                       a PLTE chunk must appear.
   
   4       8,16        Each pixel is a grayscale sample,
                       followed by an alpha sample.
   
   6       8,16        Each pixel is an R,G,B triple,
                       followed by an alpha sample.
*/

const unsigned long gAMA = 'gAMA';
const unsigned long tEXt = 'tEXt';
const unsigned long IDAT = 'IDAT';
const unsigned long IEND = 'IEND';


//#include "Defines.h" // pixmi::isLittleEndian()

class PngChunk
{
public:
   //A 4-byte unsigned integer giving the number of bytes in the chunk's data field. 
   // The length counts only the data field, not itself, the chunk type code, or the CRC. 
   // Zero is a valid length. Although encoders and decoders should treat the length as 
   // unsigned, its value must not exceed (2^31)-1 bytes.
   unsigned long length;

   // A 4-byte chunk type code. For convenience in description and in examining PNG files, 
   // type codes are restricted to consist of uppercase and lowercase ASCII letters 
   // (A-Z and a-z, or 65-90 and 97-122 decimal). However, encoders and decoders must 
   // treat the codes as fixed binary values, not character strings. For example, 
   // it would not be correct to represent the type code IDAT by the EBCDIC equivalents 
   // of those letters. Additional naming conventions for chunk types are discussed in the 
   // next section. 
   unsigned long chunkType;
   
   
   // The data bytes appropriate to the chunk type, if any. 
   // the length of this should equal "length"
   // This field can be of zero length. 
   std::vector<unsigned char> chunkData;

   //A 4-byte CRC (Cyclic Redundancy Check) calculated on the preceding bytes in the 
   // chunk, including the chunk type code and chunk data fields, but not including 
   // the length field. The CRC is always present, even for chunks containing no data. 
   // See CRC algorithm. 
   unsigned long CRC;

   void read( FILE* fp )
   {
      // get the data length
      CFileIO::ReadLong( CFileIO::BIG, fp, length );
      
      // get the chunk type
      CFileIO::ReadLong( CFileIO::BIG, fp, chunkType );
      std::cout<<((char*)&chunkType)[3]<<((char*)&chunkType)[2]<<
      ((char*)&chunkType)[1]<<((char*)&chunkType)[0]<<"\n"<<std::flush;
      
      std::cout<<"  Length: "<<length<<"\n"<<std::flush;

      // get the chunk data
      chunkData.resize( length );
      assert( chunkData.size() == length );
      for (int x = 0; x < chunkData.size(); ++x)
      {
         CFileIO::ReadByte( fp, chunkData[x] );
      }

      // get the CRC
      CFileIO::ReadLong( CFileIO::BIG, fp, CRC );
      
      // check the chunkType(4) + data(length) 
      PngCRC pcrc;
      unsigned long crc = pcrc.crc( *this );
      std::cout<<"  CRC: "<<crc<<" is "<<std::flush; 
      if (CRC == crc)
         std::cout<<"good\n"<<std::flush;
      else
         std::cout<<"bad\n"<<std::flush;
   }

      unsigned long width() const 
      { 
         int w = *((unsigned long*)&(this->chunkData[0]));
         if (pixmi::isLittleEndian())
         {
            pixmi::byteReverse( w );
         }
         return w; 
      }
      unsigned long height() const 
      { 
         int h = *((unsigned long*)&(this->chunkData[4]));
         if (pixmi::isLittleEndian())
         {
            pixmi::byteReverse( h );
         }
         return h; 
      }
      const char& pixel_depth() const { return *((char*)&this->chunkData[8]); }
      const char& color_type() const { return *((char*)&this->chunkData[9]); }
      const char& compression_method() const { return *((char*)&this->chunkData[10]); }
      const char& filter_type() const { return *((char*)&this->chunkData[11]); }
      const char& interlace_method() const { return *((char*)&this->chunkData[12]); }
};
} // namespace
#endif
