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
 * Date modified: $Date: 2003-02-22 23:53:34 $
 * Version:       $Revision: 1.3 $
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
#ifdef _MSC_VER
#  define SIREN_ULONGLONG unsigned __int64
#  define SIREN_LONGLONG __int64
#else
#  define SIREN_ULONGLONG unsigned long long
#  define SIREN_LONGLONG long long
#endif

	// Predefine frequently used signed integer types
	typedef char s8; 
	typedef short s16; 
	typedef long s32;
	typedef SIREN_LONGLONG s64;

	// Predefine frequently used unsigned integer types
	typedef unsigned char  u8;
	typedef unsigned short u16;
	typedef unsigned long u32;
	typedef SIREN_ULONGLONG u64;
}
#undef SIREN_ULONGLONG
#undef SIREN_LONGLONG	

#endif
