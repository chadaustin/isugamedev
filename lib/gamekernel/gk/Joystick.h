
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
// File:          $RCSfile: Joystick.h,v $
// Date modified: $Date: 2002-02-09 21:54:44 $
// Version:       $Revision: 1.2 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_JOYSTICK_H
#define GK_JOYSTICK_H

#include "gk/gkCommon.h"
#include <map>
#include <assert.h>

#include "gk/DigitalDevice.h"
#include "gk/AnalogDevice.h"

namespace gk {

/**
 * Joystick device driver for the GameInput system.
 *
 * Don't use this device directly (although you could, it isn't recommended).
 * Instead, use the DigitalInterface, and/or AnalogInterface classes
 * to access the button and axis data in the Joystick.  Using the Interfaces
 * class gives your application the ability to bind keys to event identifiers
 * (keybinding).  If you use this class by itself, you will not get any kind
 * of keybinding ability.
 *
 * @see AnalogDevice
 * @see DigitalDevice
 * @see Device
 */
class Joystick : public AnalogDevice, public DigitalDevice
{
public:
   /**
    * Creates a new Joystick with the given number of digital buttons and analog
    * axes.
    *
    * @param numButtons    the number of buttons on the joystick
    * @param numAxes       the number of axes supported by the joystick
    */
   Joystick( int numButtons, int numAxes )
      : DigitalDevice(), AnalogDevice()
   {
      DigitalDevice::setNumInputs( numButtons ); // num buttons
      AnalogDevice::setNumInputs( numAxes ); // num axes
      initializeMap();
   }

   /**
    * Destroys this joystick device.
    */
   virtual ~Joystick() {}

   /**
    * Updates this object to match the state of the device. The game kernel must
    * call this every frame before allowing the application to read data from
    * this device.
    *
    * <b>NOTE:</b> If you're using GameKernel system, then you don't need to
    * call this.
    */
   virtual void update()
   {
      DigitalDevice::update();
      AnalogDevice::update();
   }

   /**
    * Retrieve an input (button or axis) from this joystick.
    * 
    * @param alias   an alias bound to a Device/Input pair that was
    *                preconfigured in the GameInput input manager
    */
   virtual Input* getInput( const std::string& alias )
   {
      Input* in;
      if (NULL != (in = DigitalDevice::getInput( alias )))
      {
          return in;
      }
      else
      {
         return AnalogDevice::getInput( alias );
      }
   }

   /**
    * Don't use this function. It is not implemented.
    *
    * @see Mouse
    */
   virtual Input* getInput( const int& id )
   {
      assert( false );
      return NULL;
   }

private:
   /**
    * Initialize all the joystick input name mappings.
    */
   void initializeMap()
   {
      const std::string btnPrefix( "JOYSTICKBUTTON_" );
      const std::string axisPrefix( "JOYSTICKAXIS_" );
      int i;

      // Map the buttons
      for ( i = 0; i < numButtons(); ++i )
      {
         std::string tmp( btnPrefix );
         tmp += i;
         std::cout<<"Mapping joystick button: "<<tmp<<std::endl;
         DigitalDevice::mMap[ tmp.c_str() ] = i;
      }

      // Map the axes
      for ( i = 0; i < numAxes(); ++i )
      {
         std::string tmp( axisPrefix );
         tmp += i;
         std::cout<<"Mapping joystick axis: "<<tmp<<std::endl;
         AnalogDevice::mMap[ tmp.c_str() ] = i;
      }
   }
};

} // namespace gk

#endif
