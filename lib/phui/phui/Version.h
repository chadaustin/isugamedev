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
 * File:          $RCSfile: Version.h,v $
 * Date modified: $Date: 2003-01-04 02:31:02 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_VERSION_H
#define PHUI_VERSION_H

/**
 * This file contains two useful items.
 *    1. The preprocessor friendly PHUI_VERSION "string". It is in the form
 *       <major><minor><patch> where each part has exactly 3 digits.
 *    2. The C++ friendly variable, version, that contains the version as a
 *       string. It is in the form of <major>.<minor>.<patch> where each part
 *       has anywhere from 1 to 3 digits.
 */

/**
 * This is the "human-readable" PHUI version _string_. It is of the form
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
// The major/minor/patch version (up to 3 digits each).
#define PHUI_VERSION_MAJOR    0
#define PHUI_VERSION_MINOR    0
#define PHUI_VERSION_PATCH    1

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// To update the version number, do not modify anything below this line!!!!
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Define the helper macros
//--------------------------------------------------------------------------

// These helper macros are used build up the PHUI_VERSION macro
#define PHUI_GLUE(a,b)        a ## b
#define PHUI_XGLUE(a,b)       PHUI_GLUE(a,b)

// These helpr macros are used to facilitate a zero left fill
#define PHUI_ZEROFILL(a)        0 ## a
#define PHUI_XZEROFILL(a)       PHUI_ZEROFILL(a)

// Fix up the major version by doing a zero left fill
#if PHUI_VERSION_MAJOR < 10
#  define PHUI_VERSION_MAJOR_FILLED \
               PHUI_XZEROFILL(PHUI_XZEROFILL(PHUI_VERSION_MAJOR))
#elif PHUI_VERSION_MAJOR < 100
#  define PHUI_VERSION_MAJOR_FILLED PHUI_XZEROFILL(PHUI_VERSION_MAJOR)
#else
#  define PHUI_VERSION_MAJOR_FILLED PHUI_VERSION_MAJOR
#endif

// Fix up the minor version by doing a zero left fill
#if PHUI_VERSION_MINOR < 10
#  define PHUI_VERSION_MINOR_FILLED \
               PHUI_XZEROFILL(PHUI_XZEROFILL(PHUI_VERSION_MINOR))
#elif PHUI_VERSION_MINOR < 100
#  define PHUI_VERSION_MINOR_FILLED PHUI_XZEROFILL(PHUI_VERSION_MINOR)
#else
#  define PHUI_VERSION_MINOR_FILLED PHUI_VERSION_MINOR
#endif

// Fix up the patch version by doing a zero left fill
#if PHUI_VERSION_PATCH < 10
#  define PHUI_VERSION_PATCH_FILLED \
               PHUI_XZEROFILL(PHUI_XZEROFILL(PHUI_VERSION_PATCH))
#elif PHUI_VERSION_PATCH < 100
#  define PHUI_VERSION_PATCH_FILLED PHUI_XZEROFILL(PHUI_VERSION_PATCH)
#else
#  define PHUI_VERSION_PATCH_FILLED PHUI_VERSION_PATCH
#endif

//--------------------------------------------------------------------------
// Define the PHUI_VERSION macro
//--------------------------------------------------------------------------

// Build up the PHUI_VERSION macro by pasting the individual parts together
/**
 * The is the preprocessor-friendly version string. It is in the form of
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
#define PHUI_VERSION \
   PHUI_XGLUE( \
      PHUI_XGLUE(PHUI_VERSION_MAJOR_FILLED, PHUI_VERSION_MINOR_FILLED), \
      PHUI_VERSION_PATCH_FILLED \
   )

//--------------------------------------------------------------------------
// Declare a version string constant that can be used at runtime.
//--------------------------------------------------------------------------
namespace phui
{
   extern const char* version;
}

//--------------------------------------------------------------------------
// Cleanup after ourselves and undef all internal macros.
//--------------------------------------------------------------------------

// Undef the all helper macros
#undef PHUI_XGLUE
#undef PHUI_GLUE
#undef PHUI_ZEROFILL
#undef PHUI_XZEROFILL

// Undef the XXX_FILLED temporary macros
#undef PHUI_VERSION_MAJOR_FILLED
#undef PHUI_VERSION_MINOR_FILLED
#undef PHUI_VERSION_PATCH_FILLED

#endif
