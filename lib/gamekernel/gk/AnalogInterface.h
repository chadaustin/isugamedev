
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
// File:          $RCSfile: AnalogInterface.h,v $
// Date modified: $Date: 2002-02-06 22:22:22 $
// Version:       $Revision: 1.9 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef ANALOGINTERFACE_H
#define ANALOGINTERFACE_H

#include "gk/Common.h"
#include "gk/InputInterface.h"
#include "gk/AnalogInput.h"

/** 
 * AnalogInterface: Your Interface to all analog inputs.
 * Looking to get axis values from joystick, mouse, other other analog device?
 * This is your interface.  This Interface gives you access to the under
 * lying AnalogInput's float data variable.
 * Doesn't make sense?  Look at the nifty example below for how to get 
 * input from your game engine...
 *
 * <h3> "Example (to sample input):" </h3>
 * \code
 *    AnalogInterface mouselook_x;
 *    mouselook_x.init( "MouselookX" );
 *    float rotation = mouselook_x.getAnalogData();
 *       ... then use rotation in your camera matrix ...
 * \endcode
 *
 * Of course, this assumes that you have set up your key bindings:
 * 
 * <h3>  "Example (to configure your key bindings):" </h3>
 * \code
 *     GameInput::instance().bind( "MouselookX", "Mouse", "MOUSEAXIS_X" );
 *     GameInput::instance().bind( "MouselookY", "Mouse", "MOUSEAXIS_Y" );
 * \endcode
 *
 * @see AnalogInput
 * @see GameInput
 * @see DigitalInterface
 * @author Kevin Meinert <kevin@vrsource.org>
 * @author other happy people...
 */
class AnalogInterface : public InputInterface
{
public:
   /** Constructor */
   AnalogInterface() {}

   /** Destructor */
   virtual ~AnalogInterface() {}

   /** get the AnalogInput data from the AnalogDevice. */
   virtual float getAnalogData()
   {
      // this can surely be optimized...
      Input* in = GameInput::instance().getInput( mAlias );
      AnalogInput* ana = dynamic_cast<AnalogInput*>( in );

      if (ana == NULL)
      {
         return 0.0f;
      }

      return ana->data();
   }
};

#endif
