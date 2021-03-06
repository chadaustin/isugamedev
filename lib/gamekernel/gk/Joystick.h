
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
// Date modified: $Date: 2003-02-10 05:39:21 $
// Version:       $Revision: 1.9 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_JOYSTICK_H
#define GK_JOYSTICK_H

#include <gk/gkCommon.h>
#include <map>
#include <assert.h>

#include <gk/DigitalDevice.h>
#include <gk/AnalogDevice.h>

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
class GK_DLL Joystick : public AnalogDevice, public DigitalDevice
{
public:
   /**
    * Creates a new Joystick with initially no buttons or axes. You must call
    * setNumAxes() and setNumButtons() respectively to configure this device
    * appropriately.
    *
    * @see setNumAxes( int )
    * @see setNumButtons( int )
    */
   Joystick()
      : AnalogDevice(), DigitalDevice()
   {
      DigitalDevice::setNumInputs( 0 ); // num buttons
      AnalogDevice::setNumInputs( 0 ); // num axes
   }

   /**
    * Destroys this joystick device.
    */
   virtual ~Joystick() {}

   /**
    * Sets the number of buttons that are supported by this joystick.
    *
    * @param numButtons    the number of buttons supported by the joystick
    */
   void setNumButtons( int numButtons )
   {
      DigitalDevice::setNumInputs( numButtons );
      initializeButtonMap();
   }

   /**
    * Sets the number of axes that are supported by this joystick.
    *
    * @param numAxes       the number of axes supported by the joystick
    */
   void setNumAxes( int numAxes )
   {
      AnalogDevice::setNumInputs( numAxes );
      initializeAxisMap();
   }

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

   /** ambiguous call, not implemented
    *  cast Joystick to one of the base types or call getXxxxxInput( int )
    */
   virtual Input* getInput( const int& id )
   {
      assert( false && "ambiguous call to getInput, cannot determine source type (AnalogDevice or DigitalDevice)" );
      return NULL;
   }

   /** 
    * get analog input based on the index
    */
   virtual Input* getAnalogInput( const int& id )
   {
      return AnalogDevice::getInput( id );
   }

   /** 
    * get digital input based on the index
    */
   virtual Input* getDigitalInput( const int& id )
   {
      return DigitalDevice::getInput( id );
   }

private:
   /**
    * Initialize all the joystick button input name mappings.
    */
   void initializeButtonMap()
   {
      int i;

      // Map the buttons
      for ( i = 0; i < numButtons(); ++i )
      {
         char temp[512];
         sprintf( temp, "JOYSTICKBUTTON_%d", i );
         std::string tmp( temp );
         //std::cout<<"Mapping joystick button: "<<tmp<<std::endl;
         DigitalDevice::mMap[ tmp.c_str() ] = i;
      }

   }

   /**
    * Initialize all the joystick axes input name mappings.
    */
   void initializeAxisMap()
   {
      int i;

      // Map the axes
      for ( i = 0; i < numAxes(); ++i )
      {
         char temp[512];
         sprintf( temp, "JOYSTICKAXIS_%d", i );
         std::string tmp( temp );
         //std::cout<<"Mapping joystick axis: "<<tmp<<std::endl;
         AnalogDevice::mMap[ tmp.c_str() ] = i;
      }
   }
};

} // namespace gk

#endif
