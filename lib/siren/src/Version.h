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
 * File:          $RCSfile: Version.h,v $
 * Date modified: $Date: 2003-01-02 03:32:55 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_VERSION_H
#define SIREN_VERSION_H

/**
 * This file contains two useful items.
 *    1. The preprocessor friendly SIREN_VERSION "string". It is in the form
 *       <major><minor><patch> where each part has exactly 3 digits.
 *    2. The C++ friendly variable, version, that contains the version as a
 *       string. It is in the form of <major>.<minor>.<patch> where each part
 *       has anywhere from 1 to 3 digits.
 */

/**
 * This is the "human-readable" SIREN version _string_. It is of the form
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
// The major/minor/patch version (up to 3 digits each).
#define SIREN_VERSION_MAJOR    0
#define SIREN_VERSION_MINOR    0
#define SIREN_VERSION_PATCH    1 

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// To update the version number, do not modify anything below this line!!!!
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Define the helper macros
//--------------------------------------------------------------------------

// These helper macros are used build up the SIREN_VERSION macro
#define SIREN_GLUE(a,b)        a ## b
#define SIREN_XGLUE(a,b)       SIREN_GLUE(a,b)

// These helpr macros are used to facilitate a zero left fill
#define SIREN_ZEROFILL(a)        0 ## a
#define SIREN_XZEROFILL(a)       SIREN_ZEROFILL(a)

// Fix up the major version by doing a zero left fill
#if SIREN_VERSION_MAJOR < 10
#  define SIREN_VERSION_MAJOR_FILLED \
               SIREN_XZEROFILL(SIREN_XZEROFILL(SIREN_VERSION_MAJOR))
#elif SIREN_VERSION_MAJOR < 100
#  define SIREN_VERSION_MAJOR_FILLED SIREN_XZEROFILL(SIREN_VERSION_MAJOR)
#else
#  define SIREN_VERSION_MAJOR_FILLED SIREN_VERSION_MAJOR
#endif

// Fix up the minor version by doing a zero left fill
#if SIREN_VERSION_MINOR < 10
#  define SIREN_VERSION_MINOR_FILLED \
               SIREN_XZEROFILL(SIREN_XZEROFILL(SIREN_VERSION_MINOR))
#elif SIREN_VERSION_MINOR < 100
#  define SIREN_VERSION_MINOR_FILLED SIREN_XZEROFILL(SIREN_VERSION_MINOR)
#else
#  define SIREN_VERSION_MINOR_FILLED SIREN_VERSION_MINOR
#endif

// Fix up the patch version by doing a zero left fill
#if SIREN_VERSION_PATCH < 10
#  define SIREN_VERSION_PATCH_FILLED \
               SIREN_XZEROFILL(SIREN_XZEROFILL(SIREN_VERSION_PATCH))
#elif SIREN_VERSION_PATCH < 100
#  define SIREN_VERSION_PATCH_FILLED SIREN_XZEROFILL(SIREN_VERSION_PATCH)
#else
#  define SIREN_VERSION_PATCH_FILLED SIREN_VERSION_PATCH
#endif

//--------------------------------------------------------------------------
// Define the SIREN_VERSION macro
//--------------------------------------------------------------------------

// Build up the SIREN_VERSION macro by pasting the individual parts together
/**
 * The is the preprocessor-friendly version string. It is in the form of
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
#define SIREN_VERSION \
   SIREN_XGLUE( \
      SIREN_XGLUE(SIREN_VERSION_MAJOR_FILLED, SIREN_VERSION_MINOR_FILLED), \
      SIREN_VERSION_PATCH_FILLED \
   )

//--------------------------------------------------------------------------
// Declare a version string constant that can be used at runtime.
//--------------------------------------------------------------------------
namespace siren
{
   extern const char* version;
}

//--------------------------------------------------------------------------
// Cleanup after ourselves and undef all internal macros.
//--------------------------------------------------------------------------

// Undef the all helper macros
#undef SIREN_XGLUE
#undef SIREN_GLUE
#undef SIREN_ZEROFILL
#undef SIREN_XZEROFILL

// Undef the XXX_FILLED temporary macros
#undef SIREN_VERSION_MAJOR_FILLED
#undef SIREN_VERSION_MINOR_FILLED
#undef SIREN_VERSION_PATCH_FILLED

#endif
