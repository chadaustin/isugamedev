
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
// File:          $RCSfile: gk.h,v $
// Date modified: $Date: 2002-03-18 08:24:20 $
// Version:       $Revision: 1.5 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GK_H
#define GK_GK_H

#ifndef __cplusplus
#error GameKernel requires a C++ compiler
#endif

// include all useful gk headers for easy use by the client program
#include <gk/gkCommon.h>
#include <xdl.h>
#include <gk/AnalogInterface.h>
#include <gk/DigitalInterface.h>
#include <gk/AbstractGameApp.h>
#include <gk/IGameKernel.h>
#include <gk/GameInputConfigure.h>

// exported functions need a calling convention for win32
#ifdef WIN32
#  define GK_CALL __stdcall
#else
#  define GK_CALL
#endif

#define GK_APIFUNC(ret, decl) extern "C" XDL_FUNC ret GK_CALL decl

namespace gk {

   // Functions defined in the gk::Private namespace should not be used by
   // applications and should be considered private to the GameKernel library.
   namespace Private {

      // The following functions are extern "C" to prevent the compiler from
      // mangling the symbols since they are exported from the library.

      /**
       * Creates a new IGameKernel instance that manages the given application.
       *
       * @param app     the application to manage with the kernel
       *
       * @return  a new IGameKernel implementation if sucessful, NULL otherwise
       *
       * @private
       */
      GK_APIFUNC(IGameKernel*, GK_createGameKernel(IGameApp* app));

      /**
       * Gets the version string for this library. The formatted string is
       * returned in the form of MAJOR.MINOR.PATCH
       *
       * @return  the version string
       *
       * @private
       */
      GK_APIFUNC(const char*, GK_getVersion());

   } // namespace Private

   //--------------------------------------------------------------------------

   /**
    * Creates a new IGameKernel instance that manages the given application.
    *
    * @param app     the application to manage with the kernel
    *
    * @return  a new IGameKernel implementation if successful, NULL otherwise
    */
   inline IGameKernel* createGameKernel( IGameApp* app )
   {
      return Private::GK_createGameKernel( app );
   }

   /**
    * Gets the version string for this library in the form of MAJOR.MINOR.PATCH
    *
    * @return  the version string
    */
   inline std::string getVersion()
   {
      return std::string( Private::GK_getVersion() );
   }

} // namespace gk

#endif
