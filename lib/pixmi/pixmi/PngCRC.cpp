#include "PngChunk.h"
#include "PngCRC.h"
#include <assert.h>
#include <iostream>
#include "Defines.h"
namespace pixmi
{
PngCRC::PngCRC()
{
}

/* Return the CRC of the chunk. */
unsigned long PngCRC::crc( const PngChunk& pc )
{

// sanity check the lookup table using two alternate algorithms...
#ifdef DEBUG
  bool error = false;

  for ( int x = 0; x < 256; ++x)
  {
      if (get_crc_table_alt()[x] != get_crc_table()[x])
      {
         error = true;
         std::cout<<"error in crc table "<<get_crc_table_alt()[x]<<" != "<<get_crc_table()[x]<<"\n"<<std::flush;
      }
  }
  assert( error == false && "bad CRC lookup table" );
#endif

  
  // this data needs it's ordering considered...
  // PNG data is big endian, if we're on a little endian machine, we need to reverse it
  unsigned long chunk_type = pc.chunkType;
  if ( pixmi::isLittleEndian() )
  {
     pixmi::byteReverse( chunk_type );
  }

  unsigned long c = update_crc( 0x00000000L, (unsigned char*)&chunk_type, sizeof(unsigned long) );
  //unsigned long cprev = c;
  if (pc.chunkData.size() > 0)
  {
     c = update_crc(c, &pc.chunkData[0], pc.chunkData.size());
  }

#ifdef DEBUG
  unsigned long a = update_crc_alt( 0x00000000L, (unsigned char*)&chunk_type, sizeof(unsigned long) );
  unsigned long aprev = a;
  //cout<<aprev<<"!="<<cprev<<"\n"<<flush;

  if (pc.chunkData.size() > 0)
  {
     a = update_crc_alt(a, &pc.chunkData[0], pc.chunkData.size());
     aprev = a;
     cprev = c;
  //   std::cout<<aprev<<"!="<<cprev<<"\n"<<std::flush;
  }
  assert( a == c && "something is wrong with the crc algorithm" );
#endif

  return c;
}



} // namespace
   
