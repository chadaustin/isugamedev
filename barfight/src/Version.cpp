/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* barfight-cpr beg
 *
 * barfight - a slapstick drag-out brawl at the local pub
 * barfight is (C) Copyright 2003 by members of the
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
 * File:          $RCSfile: Version.cpp,v $
 * Date modified: $Date: 2003-02-21 08:48:46 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
#include "Version.h"

// These helper macros are used to stringify a given macro
#define BAR_STR(s)             # s
#define BAR_XSTR(s)            BAR_STR(s)

// These helper macros are used to build up the BAR_VERSION_STRING macro.
#define BAR_DOT(a,b)           a ## . ## b
#define BAR_XDOT(a,b)          BAR_DOT(a,b)

//--------------------------------------------------------------------------
// Define the BAR_VERSION_STRING macros
//--------------------------------------------------------------------------

// Create the BAR_VERSION_STRING macro
#define BAR_VERSION_STRING \
   BAR_XDOT( \
      BAR_XDOT(BAR_VERSION_MAJOR, BAR_VERSION_MINOR), \
      BAR_VERSION_PATCH \
   )

namespace bar
{
   const char* version = BAR_XSTR(BAR_VERSION_STRING);
}

// Undef all the helper macros
#undef BAR_XSTR
#undef BAR_STR
#undef BAR_DOT
#undef BAR_XDOT

// Undef the BAR_VERSION_STRING temporary macro
#undef BAR_VERSION_STRING

