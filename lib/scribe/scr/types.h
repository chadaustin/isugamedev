/*******************************************************************************
 *
 * Copyright (c) 2001 Ben Scott. All rights reserved.
 *
 * -----------------------------------------------------------------------------
 * File:          $RCSfile: types.h,v $
 * Last modified: $Date: 2002-01-27 23:44:36 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------------------
 *
 *******************************************************************************
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA.
 *
 ******************************************************************************/
#ifndef TYPES_H
#define TYPES_H 1

#include <climits>
#include <Typelist.h>
#include <TypeManip.h>
#include <scr/scrConfig.h> // namespace macros

SCR_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
// Compile-time integer type selection based on bit-size based off code from
// http://everything2.com/index.pl?node=Int%26lt%3Bbits%26gt%3B&lastnode_id=1012556
//------------------------------------------------------------------------------

// Declare our "undefined" type that will cause a compile-time error if there is
// an attempt to instantiate it.
class NoTypeFound;

//------------------------------------------------------------------------------

/**
 * Searches the given typelist TL for a type whose size is exactly equal to the
 * given number of bits.
 */
template <class TL, int bits>
struct SelectInt;

// Specialization 1: NullType encountered - end of typelist
template <int bits>
struct SelectInt< ::Loki::NullType, bits >
{
   // Empty list, no types found. Assign to NoTypeFound to cause a compile-time
   // error if the type is ever used.
   typedef NoTypeFound type;
};

// Specialization 2: Takes a <head, tail> typelist pair. If the head has exactly
// bits bits, choose it. Otherwise recurse on tail.
template <class Head, class Tail, int bits>
struct SelectInt< ::Loki::Typelist<Head,Tail>, bits >
{
   typedef typename
   ::Loki::Select< sizeof(Head)*CHAR_BIT == bits,
                   Head,
                   typename SelectInt<Tail, bits>::type
                 >::Result
   type;
};

//------------------------------------------------------------------------------

/**
 * Struct that picks a native signed integer type to match the required bit-size
 * at compile-time.
 */
template <int bits>
struct Int
{
   // List of types to check
   typedef
      TYPELIST_5( int, signed char, short, long, long long)
      SignedInts;

public:
   // This is the native type that matches the required bit size or NoTypeFound
   // if there is no such matching native type.
   typedef typename SelectInt<SignedInts, bits>::type type;
};

//------------------------------------------------------------------------------

/**
 * Struct that picks a native unsigned integer type to match the required
 * bit-size at compile time.
 */
template <int bits>
struct UInt
{
   // List of types to check
   typedef
      TYPELIST_5( unsigned int, unsigned char, unsigned short,
                  unsigned long, unsigned long long)
      UnsignedInts;

public:
   // This is the native type that matches the required bit size or NoTypeFound
   // if there is no such matching native type.
   typedef typename SelectInt<UnsignedInts, bits>::type type;
};

//------------------------------------------------------------------------------

// Predefine frequently used signed integer types
typedef Int<8>    S8;
typedef Int<16>   S16;
typedef Int<32>   S32;
typedef Int<64>   S64;

// Predefine frequently used unsigned integer types
typedef UInt<8>   U8;
typedef UInt<16>  U16;
typedef UInt<32>  U32;
typedef UInt<64>  U64;

SCR_END_NAMESPACE

#endif // ! TYPES_H
