/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Types.h,v $
 * Date modified: $Date: 2003-02-03 02:54:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_TYPES_H
#define SIREN_TYPES_H

#include <climits>
#include <Typelist.h>
#include <TypeManip.h>

//-----------------------------------------------------------------------------
// Compile-time integer type selection based on bit-size based off code from
// http://everything2.com/index.pl?node=Int%26lt%3Bbits%26gt%3B&lastnode_id=1012556
//-----------------------------------------------------------------------------


namespace siren
{
   // Put the types in their own namespace.
   namespace types
   {
      // Hide the details in a separate namespace.
      namespace details
      {
         /**
          * Declare our "undefined" type that will cause a compile-time error
          *if there is an attempt to instantiate it.
          */
         class NoTypeFound;


         /**
          * Searches the given typelist TL for a type whose size is exactly
          * equal to the given number of bits.
          */
         template< class TL, int bits >
         struct SelectInt;

         /// Specialization 1: NullType encountered - end of typelist
         template< int bits >
         struct SelectInt<Loki::NullType, bits>
         {
            /**
             * Empty list, no types found. Assign to NoTypeFound to cause a
             * compile-time error if the type is ever used.
             */
            typedef NoTypeFound type;
         };

         /**
          * Specialization 2: Takes a <head, tail> typelist pair. If the head
          * has exactly bits bits, choose it. Otherwise recurse on tail.
          */
         template< class Head, class Tail, int bits >
         struct SelectInt<Loki::Typelist<Head,Tail>, bits>
         {
            /// Defined to the type that matches the number of bits requested
            typedef typename
               Loki::Select<sizeof(Head)*CHAR_BIT == bits,
                            Head,
                            typename SelectInt<Tail, bits>::type
                           >::Result
               type;
         };
      } // namespace details

      /**
       * Struct that picks a native signed integer type to match the required
       * bit-size at compile-time.
       */
      template< int bits >
      struct Int
      {
#ifdef MSC_VER
#  define SIREN_LONGLONG __int64
#else
#  define SIREN_LONGLONG long long
#endif
         // List of types to check
         typedef TYPELIST_5(int, signed char, short, long, SIREN_LONGLONG)
                 SignedInts;
#undef SIREN_LONGLONG

      public:
         // This is the native type that matches the required bit size or
         // NoTypeFound if there is no such matching native type.
         typedef typename details::SelectInt<SignedInts, bits>::type type;
      };

      //-----------------------------------------------------------------------

      /**
       * Struct that picks a native unsigned integer type to match the required
       * bit-size at compile time.
       */
      template< int bits >
      struct UInt
      {
#ifdef MSC_VER
#  define SIREN_ULONGLONG __uint64
#else
#  define SIREN_ULONGLONG unsigned long long
#endif
         // List of types to check
         typedef TYPELIST_5(unsigned int, unsigned char, unsigned short,
                            unsigned long, SIREN_ULONGLONG)
                 UnsignedInts;
#undef SIREN_ULONGLONG

      public:
         // This is the native type that matches the required bit size or NoTypeFound
         // if there is no such matching native type.
         typedef typename details::SelectInt<UnsignedInts, bits>::type type;
      };
   } // namespace types

   // Predefine frequently used signed integer types
   typedef types::Int<8>::type   s8;
   typedef types::Int<16>::type  s16;
   typedef types::Int<32>::type  s32;
   typedef types::Int<64>::type  s64;

   // Predefine frequently used unsigned integer types
   typedef types::UInt<8>::type  u8;
   typedef types::UInt<16>::type u16;
   typedef types::UInt<32>::type u32;
   typedef types::UInt<64>::type u64;
}

#endif
