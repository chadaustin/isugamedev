/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/*************************************************************** gk-cpr beg
 * 
 * gk was forked from the original xmlpp version 0.6 under the LGPL. This
 * new, branched xmlpp is under the same LGPL (of course) and is being
 * maintained by:
 *      Kevin Meinert   <subatomic@users.sourceforge.net>
 *      Allen Bierbaum  <allenb@users.sourceforge.net>
 *      Ben Scott       <nonchocoboy@users.sourceforge.net>
 *
 * -----------------------------------------------------------------
 *
 * xmlpp - an xml parser and validator written in C++
 * copyright (c) 2000-2001 Michael Fink
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
 * File:          $RCSfile: version.cpp,v $
 * Date modified: $Date: 2003-02-08 08:54:00 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gk-cpr-end */
#include "version.h"

// These helper macros are used to stringify a given macro
#define GK_STR(s)             # s
#define GK_XSTR(s)            GK_STR(s)

// These helper macros are used to build up the GK_VERSION_STRING macro.
#define GK_DOT(a,b)           a ## . ## b
#define GK_XDOT(a,b)          GK_DOT(a,b)

//--------------------------------------------------------------------------
// Define the GK_VERSION_STRING macros
//--------------------------------------------------------------------------

// Create the GK_VERSION_STRING macro
#define GK_VERSION_STRING \
   GK_XDOT( \
      GK_XDOT(GK_VERSION_MAJOR, GK_VERSION_MINOR), \
      GK_VERSION_PATCH \
   )

namespace gk
{
   const char* version = GK_XSTR(GK_VERSION_STRING);
}

// Undef all the helper macros
#undef GK_XSTR
#undef GK_STR
#undef GK_DOT
#undef GK_XDOT

// Undef the GK_VERSION_STRING temporary macro
#undef GK_VERSION_STRING

