
//////////////////////////////////////////////////////////////////////////////
//
//                   -=    Mouse    =-
//
// Description: "Game Input driver for Mouse"
//
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
// File:          $RCSfile: Mouse.h,v $
// Date modified: $Date: 2002-02-11 03:26:03 $
// Version:       $Revision: 1.18 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_MOUSE_H
#define GK_MOUSE_H

#include "gk/gkCommon.h"
#include <map>
#include <assert.h>

#include "gk/DigitalDevice.h"
#include "gk/AnalogDevice.h"

namespace gk {

/** Mouse device driver for the GameInput system.
 *
 * Don't use this device directly (although you could, it isn't recommended).
 * Instead, use the DigitalInterface, and/or AnalogInterface classes
 * to access the button and axis data in the Mouse.  Using the Interface classes
 * gives your application the ability to bind keys to event identifiers
 * (keybinding).  If you use this class by itself, you will not get any kind
 * of keybinding ability.
 *
 * @see Keyboard
 * @see Joystick
 * @see AnalogDevice
 * @see DigitalDevice
 * @see Device
 */
class Mouse : public AnalogDevice, public DigitalDevice
{
public:
   /** Mouse Buttons.
    * This is the list of mouse button identifiers you can use.
    * When binding keys in the GameInput class, you can
    * prefix each of these with "MOUSEBUTTON_"
    * (i.e. LEFT would be "MOUSEBUTTON_LEFT").
    */
   enum Button
   {
     LEFT = 0, MIDDLE = 1, RIGHT = 2
   };

   /** constructor */
   Mouse() : AnalogDevice(), DigitalDevice()
   {
      DigitalDevice::setNumInputs( 3 ); // 3 button mouse.
      AnalogDevice::setNumInputs( 2 ); // 2 axis mouse.
      this->initialize_map();
   }

   /** destructor */
   virtual ~Mouse() {}

   /** Update: Call this on every frame of your simulation.
    * Mouse events include position change, and button change
    * you must call update() each frame of your simulation
    * before you read any data from the Mouse.
    * <b>NOTE:</b> If you're using GameKernel system, then you don't need to call this.
    */
   virtual void update()
   {
      DigitalDevice::update();
      AnalogDevice::update();
   }

   /** retrieve an input (button or axis) from the Mouse
    * @param keybinding alias: an alias bound to a Device/Input pair that was preconfigured in the GameInput input manager.
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

   /** don't use this function, it is not implemented */
   virtual Input* getInput( const int& id )
   {
      assert( false );
      Input* in;
      if (NULL != (in = DigitalDevice::getInput( id )))
      {
         return in;
      }
      else
      {
         return AnalogDevice::getInput( id );
      }
   }

private:
   void initialize_map()
   {
      DigitalDevice::mMap["MOUSEBUTTON_LEFT"] = Mouse::LEFT;
      DigitalDevice::mMap["MOUSEBUTTON_MIDDLE"] = Mouse::MIDDLE;
      DigitalDevice::mMap["MOUSEBUTTON_RIGHT"] = Mouse::RIGHT;
      AnalogDevice::mMap["MOUSEAXIS_X"] = 0;
      AnalogDevice::mMap["MOUSEAXIS_Y"] = 1;

      assert( DigitalDevice::mMap.count( "MOUSEAXIS_X" ) == 0 );
      assert( DigitalDevice::mMap.count( "MOUSEAXIS_Y" ) == 0 );
   }
};

} // namespace gk

#endif
