
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
// File:          $RCSfile: gk.cpp,v $
// Date modified: $Date: 2002-03-18 08:24:20 $
// Version:       $Revision: 1.2 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "gk/gk.h"
#include "gk/GameKernel.h"

#define GK_APIDEF(ret, name) XDL_FUNC ret GK_CALL name

namespace gk {

   namespace Private {

      // exported createGameKernel function
      GK_APIDEF(IGameKernel*, GK_createGameKernel( IGameApp* app ))
      {
         return new GameKernel( app );
      }

      // exported getVersion function
      GK_APIDEF(const char*, GK_getVersion())
      {
         return "0.1.2";
      }

   } // namespace Private

} // namespace gk
