#ifndef PNG_CRC
#define PNG_CRC

#include "Crc32.h"

namespace pixmi
{
   
// Chunk CRCs are calculated using standard CRC methods with pre and post conditioning, 
//   as defined by ISO 3309 [ISO-3309] or ITU-T V.42 [ITU-V42].
class PngChunk;
class PngCRC : public Crc32
{
public:
   PngCRC();

   /* Return the CRC of the chunk. */
   unsigned long crc( const PngChunk& pc );
};
} // namespace
#endif





