/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * Date modified: $Date: 2004-02-05 19:54:42 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_TYPES_H
#define MW_TYPES_H

namespace mw
{

#ifdef _MSC_VER

   typedef          __int8  i8;
   typedef unsigned __int8  u8;
   typedef          __int16 i16;
   typedef unsigned __int16 u16;
   typedef          __int32 i32;
   typedef unsigned __int32 u32;
   typedef          __int64 i64;
   typedef unsigned __int64 u64;

#else  // assume i386 gcc

   typedef   signed char      i8;
   typedef unsigned char      u8;
   typedef          short     i16;
   typedef unsigned short     u16;
   typedef          int       i32;
   typedef unsigned int       u32;
   typedef          long long i64;
   typedef unsigned long long u64;

#endif

}

#endif
