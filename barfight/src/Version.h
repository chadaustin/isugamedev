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
 * File:          $RCSfile: Version.h,v $
 * Date modified: $Date: 2003-02-21 08:48:46 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
#ifndef BAR_VERSION_H
#define BAR_VERSION_H

/**
 * This file contains two useful items.
 *    1. The preprocessor friendly BAR_VERSION "string". It is in the form
 *       <major><minor><patch> where each part has exactly 3 digits.
 *    2. The C++ friendly variable, version, that contains the version as a
 *       string. It is in the form of <major>.<minor>.<patch> where each part
 *       has anywhere from 1 to 3 digits.
 */

/**
 * This is the "human-readable" BAR version _string_. It is of the form
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
// The major/minor/patch version (up to 3 digits each).
#define BAR_VERSION_MAJOR    0
#define BAR_VERSION_MINOR    0
#define BAR_VERSION_PATCH    1 

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// To update the version number, do not modify anything below this line!!!!
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Define the helper macros
//--------------------------------------------------------------------------

// These helper macros are used build up the BAR_VERSION macro
#define BAR_GLUE(a,b)        a ## b
#define BAR_XGLUE(a,b)       BAR_GLUE(a,b)

// These helpr macros are used to facilitate a zero left fill
#define BAR_ZEROFILL(a)        0 ## a
#define BAR_XZEROFILL(a)       BAR_ZEROFILL(a)

// Fix up the major version by doing a zero left fill
#if BAR_VERSION_MAJOR < 10
#  define BAR_VERSION_MAJOR_FILLED \
               BAR_XZEROFILL(BAR_XZEROFILL(BAR_VERSION_MAJOR))
#elif BAR_VERSION_MAJOR < 100
#  define BAR_VERSION_MAJOR_FILLED BAR_XZEROFILL(BAR_VERSION_MAJOR)
#else
#  define BAR_VERSION_MAJOR_FILLED BAR_VERSION_MAJOR
#endif

// Fix up the minor version by doing a zero left fill
#if BAR_VERSION_MINOR < 10
#  define BAR_VERSION_MINOR_FILLED \
               BAR_XZEROFILL(BAR_XZEROFILL(BAR_VERSION_MINOR))
#elif BAR_VERSION_MINOR < 100
#  define BAR_VERSION_MINOR_FILLED BAR_XZEROFILL(BAR_VERSION_MINOR)
#else
#  define BAR_VERSION_MINOR_FILLED BAR_VERSION_MINOR
#endif

// Fix up the patch version by doing a zero left fill
#if BAR_VERSION_PATCH < 10
#  define BAR_VERSION_PATCH_FILLED \
               BAR_XZEROFILL(BAR_XZEROFILL(BAR_VERSION_PATCH))
#elif BAR_VERSION_PATCH < 100
#  define BAR_VERSION_PATCH_FILLED BAR_XZEROFILL(BAR_VERSION_PATCH)
#else
#  define BAR_VERSION_PATCH_FILLED BAR_VERSION_PATCH
#endif

//--------------------------------------------------------------------------
// Define the BAR_VERSION macro
//--------------------------------------------------------------------------

// Build up the BAR_VERSION macro by pasting the individual parts together
/**
 * The is the preprocessor-friendly version string. It is in the form of
 * <major><minor><patch>. Each part has exactly 3 digits.
 */
#define BAR_VERSION \
   BAR_XGLUE( \
      BAR_XGLUE(BAR_VERSION_MAJOR_FILLED, BAR_VERSION_MINOR_FILLED), \
      BAR_VERSION_PATCH_FILLED \
   )

//--------------------------------------------------------------------------
// Declare a version string constant that can be used at runtime.
//--------------------------------------------------------------------------
namespace bar
{
   extern const char* version;
}

//--------------------------------------------------------------------------
// Cleanup after ourselves and undef all internal macros.
//--------------------------------------------------------------------------

// Undef the all helper macros
#undef BAR_XGLUE
#undef BAR_GLUE
#undef BAR_ZEROFILL
#undef BAR_XZEROFILL

// Undef the XXX_FILLED temporary macros
#undef BAR_VERSION_MAJOR_FILLED
#undef BAR_VERSION_MINOR_FILLED
#undef BAR_VERSION_PATCH_FILLED

#endif
