
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
// Date modified: $Date: 2002-01-30 06:48:25 $
// Version:       $Revision: 1.9 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef MOUSE_INCLUDED
#define MOUSE_INCLUDED

#include <map>
#include <assert.h>

#include "DigitalDevice.h"
#include "AnalogDevice.h"

//: Mouse class
// keeps track of mouse position and button state in a simulation
// you must call update() each frame of your simulation
// before you read any data from Mouse (like position and button states)
class Mouse : public AnalogDevice, public DigitalDevice
{
public:
   enum Button
   {
     LEFT = 0, MIDDLE = 1, RIGHT = 2
   };

   Mouse::Mouse() : DigitalDevice(), AnalogDevice()
   {
      DigitalDevice::setNumInputs( 3 ); // 3 button mouse.
      AnalogDevice::setNumInputs( 2 ); // 2 axis mouse.
      Mouse::initialize_map();
   }

   virtual ~Mouse() {}

   //: Call this on every frame of your simulation
   // Mouse events include position change, and button change
   // you must call update() each frame of your simulation
   // before you read any data from Mouse (like position and button states)
   virtual void Mouse::update()
   {
      DigitalDevice::update();
      AnalogDevice::update();
   }

   virtual Input* getInput( const std::string& input_name )
   {
      Input* in;
      if (NULL != (in = DigitalDevice::getInput( input_name )))
      {
          return in;
      }
      else
      {
         return AnalogDevice::getInput( input_name );
      }
   }

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

#endif
