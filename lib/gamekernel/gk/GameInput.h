
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
// Date modified: $Date: 2002-02-18 03:11:15 $
// Version:       $Revision: 1.31 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEINPUT_H
#define GK_GAMEINPUT_H

#include "gk/gkCommon.h"
#include <string>
#include <utility> // for pair

#include "gk/Mouse.h"
#include "gk/Keyboard.h"

#include "gk/DigitalInput.h"
#include "gk/AnalogInput.h"
#include "gk/EventInput.h"

namespace gk {

// forward declare GameKernel
class GameKernel;

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
class GameInput
{
public:
   /**
    * Creates a new GameInput object with no devices or alias bindings.
    */
   GameInput()
   {
   }

   /**
    * Gets the input that the given alias has been bound to.
    *
    * @param alias      the alias bound to the input
    *
    * @return  the input if alias has been bound, NULL otherwise
    */
   Input* getInput( const std::string& alias )
   {
      if (mBindTable.count( alias ) == 0)
         return NULL;

      EventInput& event_input = mBindTable[alias];
      return &event_input;
   }

   /**
    * Gets the the Input associated with the <device,input> pair.
    *
    * @param device     the name of the device
    * @param input      the name of the input source on the device
    *
    * @return  the Input if <device,input> has already been bound.
    * @return  NULL if <device,input> has not been bound.
    */
   Input* getInput( const std::string& device, const std::string& input )
   {
      if (mDevices.count( device ) == 0)
         return NULL;

      Device* dev = mDevices[device];
      return dev->getInput( input );
   }

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
   bool addDevice( Device* device, const std::string& name )
   {
      if (mDevices.count( name ) == 0)
      {
         mDevices[ name ] = device;
         std::cout << "Added device: " << name << std::endl;
         this->refreshEventInputs();
         return true;
      }      
      std::cout << "Failed to add device: " << name << std::endl;
      return false;
   }

   /**
    * Gets the device with the given name.
    *
    * @param name    the name of the device to retrieve
    *
    * @return  a pointer to the device if it exists, NULL otherwise
    */
   Device* getDevice( const std::string& name )
   {
      std::map< std::string, Device* >::iterator itr;
      itr = mDevices.find( name );
      if ( itr != mDevices.end() )
      {
         return itr->second;
      }
      std::cout << "WARNING: cannot lookup device " << name << std::endl;
      return NULL;
   }

   /**
    * Removes the device with the given name. If no device with the given name
    * is registered, no work is done.
    *
    * @param name    the name of the device to remove
    */
   void removeDevice( const std::string& name )
   {
      std::map< std::string, Device* >::iterator itr;
      itr = mDevices.find( name );
      if ( itr != mDevices.end() )
      {
         mDevices.erase( itr );
         std::cout << "Removed device: " << name << std::endl;
         this->refreshEventInputs();
      }
   }

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
   void bind( const std::string& alias, const std::string& device, const std::string& input )
   {
      Input* in_put = getInput( device, input );
      mBindTable[alias].add( in_put );
      mBindStrings.insert( std::pair<std::string, std::pair<std::string, std::string> >( alias, std::pair<std::string, std::string>(device, input) ) ); 
      std::cout << "Bound [" << device << ":" << input << "] to [" << alias << "]" << std::endl;
   }

   
public:
   /**
    * Updates all the devices in this input manager. SystemDriver
    * implementations should call this function every frame to ensure valid
    * input within the application.
    *
    * @see GameKernel
    * @see SystemDriver
    */
   void update()
   {
      std::map<std::string, Device*>::iterator itr;
      for( itr = mDevices.begin(); itr != mDevices.end(); ++itr )
      {
         itr->second->update();
      }
   }

private:
   /**
    * Refreshes all bindings. This allows you to swap out a device and still
    * maintain the bindings to it.
    */
   void refreshEventInputs()
   {
      // reset each EventInput object (this removes all binding info from them...)
      std::map<std::string, EventInput>::iterator itr;
      for (itr = mBindTable.begin(); itr != mBindTable.end(); ++itr)
      {
         (*itr).second.clear();
      }
      
      // re-add all binding info to EventInputs based on currently added devices..
      std::multimap<std::string, std::pair<std::string, std::string> >::iterator it;
      for (it = mBindStrings.begin(); it != mBindStrings.end(); ++it)
      {
         Input* in_put = getInput( (*it).second.first, (*it).second.second );
         mBindTable[(*it).first].add( in_put );
         //std::cout << "   refresh: " << (*it).first << " " << (*it).second.first << " " << (*it).second.second << std::endl;
      }
   }

private:
   // database of all bound items.
   std::multimap<std::string, std::pair<std::string, std::string> > mBindStrings;

   // quick lookup of alias -> Input
   std::map<std::string, EventInput> mBindTable;

   // currently registred devices.
   std::map<std::string, Device*> mDevices;
};

/**
 * Device wrapper that provides automatic addition and removal of the contained
 * device with the input manager.
 *
 * @param Type    the type of device to manage
 */
template< class Type >
class DeviceHandle
{
public:
   /**
    * Creates and instance of the device type and adds it to the input manager.
    *
    * @param name    the name of the device
    * @param kernel  the kernel with which to attach this device to
    *
    * @pre kernel != NULL
    */
   DeviceHandle( const std::string& name, GameKernel* kernel )
      : mName( name ), mKernel( kernel )
   {
      mDevice = new Type();
      mKernel->getInput()->addDevice( mDevice, name );
   }

   /**
    * Removes the device from the input manager and destroys it. Note that the
    * device's memory will be released.
    */
   ~DeviceHandle()
   {
      mKernel->getInput()->removeDevice( mName );
      delete mDevice;
   }

   /**
    * Gets the contained device.
    *
    * @return  a pointer to the contained device
    */
   Type* getDevice()
   {
      return mDevice;
   }

   /**
    * Gets the contained device.
    *
    * @return  a pointer to the contained device
    */
   const Type* getDevice() const
   {
      return mDevice;
   }

   /**
    * Gets the name of the contained device.
    *
    * @return  the name of the contained device
    */
   const std::string& getName() const
   {
      return mName;
   }

private:
   /**
    * The name of the device.
    */
   std::string mName;

   /**
    * The kernel to which the device is attached.
    */
   GameKernel* mKernel;

   /**
    * The managed device.
    */
   Type* mDevice;
};

} // namespace gk

#endif
