#ifndef LR_TYPES_H
#define LR_TYPES_H

namespace lr
{
 
   /**
    * an enumeration for the various types of entities that could be in a slot
    * in the level
    */
   enum positionType {empty, brick, ladder, wire, money};

   /**
    * an enumeration for the various states the player could be in
    */
   enum playerState {runRight, runLeft, climbRight, climbLeft, hangRight, hangLeft};

   enum textureState {run1, run2, climb1, climb2, hang1, hang2};
   
   // typedefs for a bunch of the major sizes in c++
   typedef   signed char      i8;
   typedef unsigned int       u8;
   typedef          short     i16;
   typedef unsigned short     u16;
   typedef          int       i32;
   typedef unsigned int       u32;
   typedef          long long i64;
   typedef unsigned long long u64;
}

#endif
