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
 * File:          $RCSfile: Version.cpp,v $
 * Date modified: $Date: 2003-01-02 03:32:55 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include "Version.h"

// These helper macros are used to stringify a given macro
#define SIREN_STR(s)             # s
#define SIREN_XSTR(s)            SIREN_STR(s)

// These helper macros are used to build up the SIREN_VERSION_STRING macro.
#define SIREN_DOT(a,b)           a ## . ## b
#define SIREN_XDOT(a,b)          SIREN_DOT(a,b)

//--------------------------------------------------------------------------
// Define the SIREN_VERSION_STRING macros
//--------------------------------------------------------------------------

// Create the SIREN_VERSION_STRING macro
#define SIREN_VERSION_STRING \
   SIREN_XDOT( \
      SIREN_XDOT(SIREN_VERSION_MAJOR, SIREN_VERSION_MINOR), \
      SIREN_VERSION_PATCH \
   )

namespace siren
{
   const char* version = SIREN_XSTR(SIREN_VERSION_STRING);
}

// Undef all the helper macros
#undef SIREN_XSTR
#undef SIREN_STR
#undef SIREN_DOT
#undef SIREN_XDOT

// Undef the SIREN_VERSION_STRING temporary macro
#undef SIREN_VERSION_STRING

