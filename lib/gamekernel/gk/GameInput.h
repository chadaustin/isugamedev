
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
// File:          $RCSfile: GameInput.h,v $
// Date modified: $Date: 2002-03-21 05:57:16 $
// Version:       $Revision: 1.36 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEINPUT_H
#define GK_GAMEINPUT_H

#include <gk/gkCommon.h>
#include <map>
#include <utility> // for pair
#include <gk/IGameInput.h>
#include <gk/IGameKernel.h>

namespace gk {
/**
 * Input manager for game input.
 * Try to use the Interface classes instead of this class directly
 * (i.e. use DigitalInterface or AnalogInterface)
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
 *     gameKernel->getInput()->bind( "Accelerate", "Keyboard", "KEY_UPARROW" );
 *     gameKernel->getInput()->bind( "StrafeLeft", "Keyboard", "KEY_LEFTARROW" );
 *     gameKernel->getInput()->bind( "Accelerate", "Keyboard", "KEY_RIGHTARROW" );
 * \endcode
 *
 * @see DigitalInterface
 * @see AnalogInterface
 * @author Kevin Meinert <kevin@vrsource.org>
 */
class GameInput : public DLLImpl< IGameInput >
{
public:
   /**
    * Creates a new GameInput object with no devices or alias bindings.
    */
   GameInput();

   /**
    * Releases all devices associated with this input manager.
    */
   virtual ~GameInput();

   /**
    * Gets the input that the given alias has been bound to.
    *
    * @param alias      the alias bound to the input
    *
    * @return  the input if alias has been bound, NULL otherwise
    */
   Input* getInput( const std::string& alias );

   /**
    * Gets the the Input associated with the <device,input> pair.
    *
    * @param device     the name of the device
    * @param input      the name of the input source on the device
    *
    * @return  the Input if <device,input> has already been bound.
    * @return  NULL if <device,input> has not been bound.
    */
   Input* getInput( const std::string& device, const std::string& input );

   /**
    * Add a device to this input manager. Once added, the device's inputs will
    * be available for binding. The device should not already have been added to
    * this input manager.
    *
    * @param device     the device to add
    * @param name       the unique name for the device
    *
    * @return  true if successful, false otherwise
    */
   bool addDevice( IDevice* device, const std::string& name );

   /**
    * Gets the device with the given name.
    *
    * @param name    the name of the device to retrieve
    *
    * @return  a pointer to the device if it exists, NULL otherwise
    */
   IDevice* getDevice( const std::string& name );

   /**
    * Removes the device with the given name. If no device with the given name
    * is registered, no work is done.
    *
    * @param name    the name of the device to remove
    */
   void removeDevice( const std::string& name );

   /**
    *  Bind an alias to a device's input. This allows you to retrieve that input
    *  at a later time using your alias without regard to what that alias was
    *  bound to.
    *
    *  @param alias     the name by which your application wishes to refer to
    *                   the device's input
    *  @param device    the name of the device
    *  @param input     the name of the input on the device
    */
   void bind( const std::string& alias, const std::string& device,
              const std::string& input );

   /**
    * Updates all the devices in this input manager. SystemDriver
    * implementations should call this function every frame to ensure valid
    * input within the application.
    *
    * @see IGameKernel
    * @see SystemDriver
    */
   void update();

private:
   /**
    * Refreshes all bindings. This allows you to swap out a device and still
    * maintain the bindings to it.
    */
   void refreshEventInputs();

private:
   // database of all bound items.
   std::multimap<std::string, std::pair<std::string, std::string> > mBindStrings;

   // quick lookup of alias -> Input
   std::map<std::string, EventInput> mBindTable;

   // currently registred devices.
   std::map<std::string, IDevice*> mDevices;
};

} // namespace gk

#endif
