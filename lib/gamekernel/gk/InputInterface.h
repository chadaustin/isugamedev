
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
// File:          $RCSfile: InputInterface.h,v $
// Date modified: $Date: 2002-02-09 21:54:44 $
// Version:       $Revision: 1.8 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_INPUTINTERFACE_H
#define GK_INPUTINTERFACE_H

#include "gk/gkCommon.h"
#include <string>

namespace gk {

class InputInterface
{
public:
   InputInterface()
   {
   }
   virtual ~InputInterface() {}

   /* initialize this interface with the alias to the input */
   virtual void init( const std::string& alias )
   {
      mAlias = alias;
      std::cout << "Created interface to " << alias << std::endl;
   }


public:
   std::string mAlias;
};

} // namespace gk

#endif
