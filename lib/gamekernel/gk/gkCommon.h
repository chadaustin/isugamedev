
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
// Date modified: $Date: 2002-02-06 22:22:22 $
// Version:       $Revision: 1.2 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GKCOMMON_H
#define GKCOMMON_H

#ifdef _MSC_VER
   // disable 'identifier was truncated to 255 characters in debug information' warning
#  pragma warning(disable: 4786)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

// macros to make namespace definitions easier on some editors
#define GK_BEGIN_NAMESPACE namespace gk {
#define GK_END_NAMESPACE }

// just in case we decide to change the namespace later or compile it out ...
// This macro will first ensure that the namespace does exist before it
// declares that it is being used. This is done for compilation safety.
#define GK_USING_NAMESPACE namespace gk {} using namespace gk;

#endif // ! GKCOMMON_H
