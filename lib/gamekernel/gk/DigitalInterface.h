
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
// File:          $RCSfile: DigitalInterface.h,v $
// Date modified: $Date: 2002-02-11 05:26:03 $
// Version:       $Revision: 1.12 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_DIGITALINTERFACE_H
#define GK_DIGITALINTERFACE_H

#include "gk/gkCommon.h"
#include "InputInterface.h"
#include "DigitalInput.h"

namespace gk {

/**
 * DigitalInterface: Your Interface to all digital inputs.
 * Looking to get button presses and other digital events?
 * This is your interface.  This Interface gives you access to the under
 * lying DigitalInput's DigitalInput::EdgeTriggerState state variable.
 * Doesn't make sense?  Look at the nifty example below for how to get
 * input from your game engine...
 *
 * <h3> "Example (to sample input):" </h3>
 * \code
 *    DigitalInterface accelerate;
 *    accelerate.init( "Accelerate" );
 *    if (accelerate.getDigitalData() == DigitalInput::DOWN)
 *       ... do something ...
 * \endcode
 *
 * Of course, this assumes that you have set up your key bindings:
 *
 * <h3>  "Example (to configure your key bindings):" </h3>
 * \code
 *     GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_UPARROW" );
 *     GameInput::instance().bind( "StrafeLeft", "Keyboard", "KEY_LEFTARROW" );
 *     GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_RIGHTARROW" );
 * \endcode
 *
 * @see DigitalInput
 * @see GameInput
 * @see AnalogInterface
 * @author Kevin Meinert <kevin@vrsource.org>
 */
class DigitalInterface : public InputInterface
{
public:
   /**
    * Creates a new interface to a digital input. You can't retrieve any data
    * from this interface until you initialize it with an alias by calling
    * init(..). See the class documentation for details.
    *
    * @see DigitalInterface
    * @see InputInterface::init( const std::string& )
    */
   DigitalInterface() {}

   /**
    * Destroys this interface to a digital input.
    */
   virtual ~DigitalInterface() {}

   /**
    * Gets the digital input data from the DigitalDevice this object is an
    * interface to.
    *
    * @see DigitalInput
    */
   virtual DigitalInput::EdgeTriggerState getDigitalData()
   {
      // this can surely be optimized...
      Input* in = GameInput::instance().getInput( mAlias );
      DigitalInput* dig = dynamic_cast<DigitalInput*>( in );

      if (dig == NULL)
         return DigitalInput::UP;

      return dig->edgeState();
   }
};

} // namespace gk

#endif
