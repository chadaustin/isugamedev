
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: gkCommon.h,v $
// Date modified: $Date: 2003-02-09 07:43:03 $
// Version:       $Revision: 1.5 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GKCOMMON_H
#define GK_GKCOMMON_H

#ifdef _MSC_VER
   // disable 'identifier was truncated to 255 characters in debug information' warning
#  pragma warning(disable: 4786)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/**
 * Macros for declaring whether we are exporting or importing symbols from a
 * library when we compile. This is really only needed for Win32 libraries.
 */
#ifdef WIN32
#  define GK_EXPORT __declspec( dllexport )
#  define GK_IMPORT __declspec( dllimport )
#else
#  define GK_EXPORT
#  define GK_IMPORT
#endif

#ifdef GK_BUILD_DLL
#  define GK_DLL     GK_EXPORT
#elif defined( GK_USE_DLL )
#  define GK_DLL     GK_IMPORT
#else
#  define GK_DLL
#endif

#endif
