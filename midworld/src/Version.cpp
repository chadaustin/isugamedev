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
 * File:          $RCSfile: Version.cpp,v $
 * Date modified: $Date: 2002-11-26 02:54:02 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "Version.h"

// These helper macros are used to stringify a given macro
#define MW_STR(s)             # s
#define MW_XSTR(s)            MW_STR(s)

// These helper macros are used to build up the MW_VERSION_STRING macro.
#define MW_DOT(a,b)           a ## . ## b
#define MW_XDOT(a,b)          MW_DOT(a,b)

//--------------------------------------------------------------------------
// Define the MW_VERSION_STRING macros
//--------------------------------------------------------------------------

// Create the MW_VERSION_STRING macro
#define MW_VERSION_STRING \
   MW_XDOT( \
      MW_XDOT(MW_VERSION_MAJOR, MW_VERSION_MINOR), \
      MW_VERSION_PATCH \
   )

namespace mw
{
   const char* version = MW_XSTR(MW_VERSION_STRING);
}

// Undef all the helper macros
#undef MW_XSTR
#undef MW_STR
#undef MW_DOT
#undef MW_XDOT

// Undef the MW_VERSION_STRING temporary macro
#undef MW_VERSION_STRING

