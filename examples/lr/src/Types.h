#ifndef LR_TYPES_H
#define LR_TYPES_H

namespace lr
{
 
   /** an enum for the various different orientations that the player can be in
    * relative to the badguy.
    */
   enum playerRelativePos { upright, rightup, downright, rightdown, upleft, leftup, downleft, leftdown};
   
   /**
    * an enumeration for the various types of entities that could be in a slot
    * in the level
    */
   enum positionType {empty, brick, ladder, wire, money};

   /**
    * an enumeration for the various states the player could be in
    */
   enum playerState {runright, runleft, climb, hangright, hangleft};

   enum textureState {runleft1, runleft2, runleft3, runright1, runright2, runright3, climb1, climb2, hangright1, hangright2, hangright3, hangleft1, hangleft2, hangleft3};
   
   // typedefs for a bunch of the major sizes in c++
   #ifndef _MSC_VER // assume i386
      typedef   signed char      i8;
      typedef unsigned int       u8;
      typedef          short     i16;
      typedef unsigned short     u16;
      typedef          int       i32;
      typedef unsigned int       u32;
      typedef          long long i64;
      typedef unsigned long long u64;
   #else // we're in windoze
      typedef          __int8  i8;
      typedef unsigned __int8  u8;
      typedef          __int16 i16;
      typedef unsigned __int16 u16;
      typedef          __int32 i32;
      typedef unsigned __int32 u32;
      typedef          __int64 i64;
      typedef unsigned __int64 u64;
   #endif

   // now give the windows equivelent

}

#endif
