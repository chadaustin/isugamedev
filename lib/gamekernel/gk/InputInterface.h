
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
// Date modified: $Date: 2002-02-20 02:58:40 $
// Version:       $Revision: 1.11 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_INPUTINTERFACE_H
#define GK_INPUTINTERFACE_H

#include "gk/gkCommon.h"
#include <string>
#include "gk/GameKernel.h"

namespace gk 
{

/**
 * Base class for interfaces to inputs. An input interface allows your
 * application to get data from a device's input by referring to it by it's
 * alias. All interactions with the GameInput input manager are hidden and
 * automated for you. It is recommended that you use an InputInterface
 * implementation to gain access to input data rather than work through the
 * GameInput singleton yourself.
 */
class InputInterface
{
public:
   /**
    * Creates a new input interface to a device. You can't retrieve any data
    * from this interface until you initialize it with an alias by calling
    * init(..).
    *
    * @see init( const std::string& )
    */
   InputInterface()
   {}

   /**
    * Destroys this interface to a digital input.
    */
   virtual ~InputInterface() {}

   /**
    * Initialize this interface with the given alias to a device's input. Once
    * initialized with the given alias, you can retrieve the data on that
    * device's input using the implementation's getXXXData() method.
    *
    * @param alias      the alias to an input you wish to get input data from
    */
   virtual void init( const std::string& alias, GameKernel* kernel )
   {
      mAlias = alias;
      mKernel = kernel;
      std::cout << "Created interface to " << alias << std::endl;
   }

protected:
   /**
    * The kernel whose input this object interfaces with.
    */
   GameKernel* mKernel;

public:
   std::string mAlias;
};

} // namespace gk

#endif
