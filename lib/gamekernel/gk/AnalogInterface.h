
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
// Date modified: $Date: 2002-02-18 03:11:15 $
// Version:       $Revision: 1.14 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_ANALOGINTERFACE_H
#define GK_ANALOGINTERFACE_H

#include "gk/gkCommon.h"
#include "gk/InputInterface.h"
#include "gk/AnalogInput.h"

namespace gk {

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
 * Of course, this assumes that you have set up your bindings:
 *
 * <h3>  "Example (to configure your bindings):" </h3>
 * \code
 *     GameInput::instance().bind( "MouselookX", "Mouse", "MOUSEAXIS_X" );
 *     GameInput::instance().bind( "MouselookY", "Mouse", "MOUSEAXIS_Y" );
 * \endcode
 *
 * @see AnalogInput
 * @see GameInput
 * @see DigitalInterface
 * @author Kevin Meinert <kevin@vrsource.org>
 */
class AnalogInterface : public InputInterface
{
public:
   /**
    * Creates a new interface to an analog input. You can't retrieve any data
    * from this interface until you initialize it with an alias by calling
    * init(..). See the class documentation for details.
    *
    * @see AnalogInterface
    * @see InputInterface::init( const std::string& )
    */
   AnalogInterface( GameKernel* kernel )
      : InputInterface( kernel )
   {}

   /**
    * Destroys this interface to an analog input.
    */
   virtual ~AnalogInterface() {}

   /**
    * Gets the analog input data from the AnalogDevice this object is an
    * interface to.
    *
    * @see AnalogInput
    */
   virtual float getAnalogData()
   {
      // this can surely be optimized...
      Input* in = mKernel->getInput()->getInput( mAlias );
      AnalogInput* ana = dynamic_cast<AnalogInput*>( in );

      if (ana == NULL)
      {
         return 0.0f;
      }

      return ana->data();
   }
};

} // namespace gk

#endif
