
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
// File:          $RCSfile: AnalogDevice.h,v $
// Date modified: $Date: 2002-03-21 05:04:08 $
// Version:       $Revision: 1.11 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_ANALOGDEVICE_H
#define GK_ANALOGDEVICE_H

#include <gk/gkCommon.h>
#include <gk/Device.h>
#include <gk/AnalogInput.h>

namespace gk {

/**
 * This abstract class describes an analog device such as a mouse or joystick.
 * An analog device is described by its inputs. In an analog device each input
 * is an axis. An analog device can contain any number of inputs (axes).
 *
 * @see AnalogInput
 * @see Device
 */
class AnalogDevice : public TypedDevice<AnalogInput>
{
protected:
   /**
    * This class is abstract. You can't create an AnalogDevice directly.
    * Instead you should create a specific implementation of AnalogDevice.
    */
   AnalogDevice() {}

public:
   /**
    * Gets the xth axial input in this device.
    *
    * @param x    the zero-based index to the input
    * @pre 0 <= x < numAxes()
    *
    * @return  the AnalogInput corresponding to index x
    */
   AnalogInput& axis( int x )
   {
      Input* in = TypedDevice<AnalogInput>::getInput( x );
      AnalogInput* ain = dynamic_cast<AnalogInput*>( in );
      assert( ain != NULL && "this shouldn't happen" );
      return *ain;
   }

   /**
    * Gets the axial input assigned to the given name.
    *
    * @param name    the name of the input to retrieve
    *
    * @return  the AnalogInput corresponding to name or NULL if no input is
    *          assigned to name
    */
   AnalogInput* axis( const std::string& name )
   {
      Input* in = TypedDevice<AnalogInput>::getInput( name );
      return dynamic_cast<AnalogInput*>( in );
   }

   /**
    * Gets the number of axes on this analog device.
    *
    * @return  the number of axes
    */
   int numAxes() const
   {
      return numInputs();
   }
};

} // namespace gk

#endif
