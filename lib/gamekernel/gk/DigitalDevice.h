
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
// File:          $RCSfile: DigitalDevice.h,v $
// Date modified: $Date: 2003-02-09 07:43:03 $
// Version:       $Revision: 1.14 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_DIGITALDEVICE_H
#define GK_DIGITALDEVICE_H

#include <gk/gkCommon.h>
#include <gk/TypedDevice.h>
#include <gk/DigitalInput.h>

namespace gk {

/* a digital device
 * a keyboard, mouse, or joystick (for example) may be a digital device
 * a digital device can contain many inputs (or buttons)
 */
class GK_DLL DigitalDevice : public TypedDevice<DigitalInput>
{
public:
   DigitalDevice() {}
   DigitalInput& button( int x )
   {
      Input* in = TypedDevice<DigitalInput>::getInput( x );
      DigitalInput* din = dynamic_cast<DigitalInput*>( in );
      assert( din != NULL );
      return *din;
   }
   DigitalInput* button( const std::string& x )
   {
      Input* in = TypedDevice<DigitalInput>::getInput( x );
      return dynamic_cast<DigitalInput*>( in );
   }

   /**
    * Gets the number of buttons supported by this device.
    *
    * @return  the number of buttons on the device
    */
   int numButtons() const
   {
      return numInputs();
   }
};

} // namespace gk

#endif
