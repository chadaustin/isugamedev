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
 * File:          $RCSfile: Version.h,v $
 * Date modified: $Date: 2002-10-28 07:41:20 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_VERSION_H
#define MW_VERSION_H

/**
 * This file contains two useful items.
 *    1. The preprocessor friendly MW_VERSION "string". It is in the form
 *       <major><minor><patch> where each part has exactly 3 digits.
 *    2. The C++ friendly variable, version, that contains the version as a
 *       string. It is in the form of <major>.<minor>.<patch> where each part
 *       has anywhere from 1 to 3 digits.
 */

/**
 * This is the "human-readable" MW version _string_. It is of the form
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
// The major/minor/patch version (up to 3 digits each).
#define MW_VERSION_MAJOR    0
#define MW_VERSION_MINOR    3
#define MW_VERSION_PATCH    0 

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// To update the version number, do not modify anything below this line!!!!
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Define the helper macros
//--------------------------------------------------------------------------

// These helper macros are used build up the MW_VERSION macro
#define MW_GLUE(a,b)        a ## b
#define MW_XGLUE(a,b)       MW_GLUE(a,b)

// These helper macros are used to stringify a given macro
#define MW_STR(s)             # s
#define MW_XSTR(s)            MW_STR(s)

// These helper macros are used to build up the MW_VERSION_STRING macro.
#define MW_DOT(a,b)           a ## . ## b
#define MW_XDOT(a,b)          MW_DOT(a,b)

// These helpr macros are used to facilitate a zero left fill
#define MW_ZEROFILL(a)        0 ## a
#define MW_XZEROFILL(a)       MW_ZEROFILL(a)

// Fix up the major version by doing a zero left fill
#if MW_VERSION_MAJOR < 10
#  define MW_VERSION_MAJOR_FILLED \
               MW_XZEROFILL(MW_XZEROFILL(MW_VERSION_MAJOR))
#elif MW_VERSION_MAJOR < 100
#  define MW_VERSION_MAJOR_FILLED MW_XZEROFILL(MW_VERSION_MAJOR)
#else
#  define MW_VERSION_MAJOR_FILLED MW_VERSION_MAJOR
#endif

// Fix up the minor version by doing a zero left fill
#if MW_VERSION_MINOR < 10
#  define MW_VERSION_MINOR_FILLED \
               MW_XZEROFILL(MW_XZEROFILL(MW_VERSION_MINOR))
#elif MW_VERSION_MINOR < 100
#  define MW_VERSION_MINOR_FILLED MW_XZEROFILL(MW_VERSION_MINOR)
#else
#  define MW_VERSION_MINOR_FILLED MW_VERSION_MINOR
#endif

// Fix up the patch version by doing a zero left fill
#if MW_VERSION_PATCH < 10
#  define MW_VERSION_PATCH_FILLED \
               MW_XZEROFILL(MW_XZEROFILL(MW_VERSION_PATCH))
#elif MW_VERSION_PATCH < 100
#  define MW_VERSION_PATCH_FILLED MW_XZEROFILL(MW_VERSION_PATCH)
#else
#  define MW_VERSION_PATCH_FILLED MW_VERSION_PATCH
#endif

//--------------------------------------------------------------------------
// Define the MW_VERSION and MW_VERSION_STRING macros
//--------------------------------------------------------------------------

// Build up the MW_VERSION macro by pasting the individual parts together
/**
 * The is the preprocessor-friendly version string. It is in the form of
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
#define MW_VERSION \
   MW_XGLUE( \
      MW_XGLUE(MW_VERSION_MAJOR_FILLED, MW_VERSION_MINOR_FILLED), \
      MW_VERSION_PATCH_FILLED \
   )

// Create the MW_VERSION_STRING macro
#define MW_VERSION_STRING \
   MW_XDOT( \
      MW_XDOT(MW_VERSION_MAJOR, MW_VERSION_MINOR), \
      MW_VERSION_PATCH \
   )

//--------------------------------------------------------------------------
// Declare a version string constant that can be used at runtime.
//--------------------------------------------------------------------------
namespace mw
{
   const char* version = MW_XSTR(MW_VERSION_STRING);
}

//--------------------------------------------------------------------------
// Cleanup after ourselves and undef all internal macros.
//--------------------------------------------------------------------------

// Undef the all helper macros
#undef MW_XGLUE
#undef MW_GLUE
#undef MW_XSTR
#undef MW_STR
#undef MW_ZEROFILL
#undef MW_XZEROFILL
#undef MW_XDOT
#undef MW_DOT

// Undef the MW_VERSION_STRING temporary macro
#undef MW_VERSION_STRING

// Undef the XXX_FILLED temporary macros
#undef MW_VERSION_MAJOR_FILLED
#undef MW_VERSION_MINOR_FILLED
#undef MW_VERSION_PATCH_FILLED

// Undef the macro for each version part
#undef MW_VERSION_MAJOR
#undef MW_VERSION_MINOR
#undef MW_VERSION_PATCH

#endif
