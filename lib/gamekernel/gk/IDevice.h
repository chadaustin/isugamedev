
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
// File:          $RCSfile: IDevice.h,v $
// Date modified: $Date: 2002-03-21 05:57:16 $
// Version:       $Revision: 1.1 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_IDEVICE_H
#define GK_IDEVICE_H

#include <gk/gkCommon.h>
#include <string>
#include <gk/DLLInterface.h>
#include <gk/Input.h>

namespace gk {

/**
 * Interface for an input device attached to the system. An input device is
 * described by the inputs attached to it. A device may have any number of
 * inputs associated with it. Each input has both a string name and an integer
 * ID associated with it so that it can be easily accessed.
 */
class IDevice : public DLLInterface
{
public:
   /**
    * Gets the input on this device with the associated name. If there is no
    * input with the given name, this method returns NULL.
    *
    * @param name    the name of the input to retrieve
    *
    * @return  the input if it exists, NULL otherwise
    */
   virtual Input* getInput( const std::string& name ) = 0;

   /**
    * Gest the input on this device with the associated integer ID. If there is
    * no input with the given ID, this method returns NULL.
    *
    * @param id      the ID of the input to retrieve
    *
    * @return  the input if it exists, NULL otherwise
    */
   virtual Input* getInput( const int& id ) = 0;

   /**
    * @internal
    *
    * Updates the state of all inputs on this device. You should never call
    * this directly. The IGameKernel instance will call this method every
    * frame for you.
    */
   virtual void update() = 0;
};

}

#endif
