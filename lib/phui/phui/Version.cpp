/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * Date modified: $Date: 2003-01-04 02:31:02 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "Version.h"

// These helper macros are used to stringify a given macro
#define PHUI_STR(s)             # s
#define PHUI_XSTR(s)            PHUI_STR(s)

// These helper macros are used to build up the PHUI_VERSION_STRING macro.
#define PHUI_DOT(a,b)           a ## . ## b
#define PHUI_XDOT(a,b)          PHUI_DOT(a,b)

//--------------------------------------------------------------------------
// Define the PHUI_VERSION_STRING macros
//--------------------------------------------------------------------------

// Create the PHUI_VERSION_STRING macro
#define PHUI_VERSION_STRING \
   PHUI_XDOT( \
      PHUI_XDOT(PHUI_VERSION_MAJOR, PHUI_VERSION_MINOR), \
      PHUI_VERSION_PATCH \
   )

namespace phui
{
   const char* version = PHUI_XSTR(PHUI_VERSION_STRING);
}

// Undef all the helper macros
#undef PHUI_XSTR
#undef PHUI_STR
#undef PHUI_DOT
#undef PHUI_XDOT

// Undef the PHUI_VERSION_STRING temporary macro
#undef PHUI_VERSION_STRING
