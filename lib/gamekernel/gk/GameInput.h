
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
// Date modified: $Date: 2002-02-09 21:54:44 $
// Version:       $Revision: 1.27 $
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
#include "gk/Singleton.h"

#include "gk/DigitalInput.h"
#include "gk/AnalogInput.h"
#include "gk/EventInput.h"

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
 *     GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_UPARROW" );
 *     GameInput::instance().bind( "StrafeLeft", "Keyboard", "KEY_LEFTARROW" );
 *     GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_RIGHTARROW" );
 * \endcode
 *
 * @see DigitalInterface
 * @see AnalogInterface
 * @see Singleton<GameInput>
 * @author Kevin Meinert <kevin@vrsource.org>
 * @author other happy people...
 */
class GameInput : public Singleton<GameInput>
{
public:
   GameInput()
   {
   }

   /** return an Input ptr
    * give the alias to the input
    * i.e. ACCELERATE_ACTION
    * !RETURN: NULL - Not found
    */
   Input* getInput( const std::string& alias )
   {
      if (mBindTable.count( alias ) == 0)
         return NULL;

      EventInput& event_input = mBindTable[alias];
      return &event_input;
   }

   /** Return an Input ptr
    * give the real Device name (i.e. Keyboard) and
    * give the real input name within that Device (i.e. KEY_UPARROW)
    * !RETURN: NULL - Not found
    */
   Input* getInput( const std::string& device, const std::string& input )
   {
      if (mDevices.count( device ) == 0)
         return NULL;

      Device* dev = mDevices[device];
      return dev->getInput( input );
   }

   /**
    * Add a device to this input manager.
    *
    * Add the devPtr to the device Array, devPtr should
    * not already be in the array.
    *
    * @param devPtr     the device to add
    * @param name       the unique name for the device
    *
    * @return  true if successful, false otherwise
    *
    * MODIFIES: self
    */
   bool addDevice( Device* devPtr, const std::string& name )
   {
      if (mDevices.count( name ) == 0)
      {
         mDevices[ name ] = devPtr;
         std::cout << "Added device: " << name << std::endl;
         return true;
         this->refreshEventInputs();
      }      
      std::cout << "Failed to add device: " << name << std::endl;
      return false;
   }

   /**
    * Gets the device with the given name.
    *
    * @name    the name of the device to retrieve
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
    * @name    the name of the device to remove
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
    *  bind an alias to a device's input
    */
   void bind( const std::string& alias, const std::string& device, const std::string& input )
   {
      Input* in_put = GameInput::instance().getInput( device, input );
      mBindTable[alias].bind( in_put, device, input );
      std::cout << "Bound [" << device << ":" << input << "] to [" << alias << "]" << std::endl;
   }

   
public:
   /** update function.
    * if using the GameInput manager without GameKernel, you will need to
    * call this function every frame to ensure valid input
    */
   inline void update()
   {
      std::map<std::string, Device*>::iterator itr;
      for( itr = mDevices.begin(); itr != mDevices.end(); ++itr )
      {
         itr->second->update();
      }
   }

   void refreshEventInputs()
   {
      std::map<std::string, EventInput>::iterator it;
      for (it = mBindTable.begin(); it != mBindTable.end(); ++it)
      {
         (*it).second.refresh();
      }
   }

private:
   std::map<std::string, EventInput> mBindTable;
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
    */
   DeviceHandle( const std::string& name )
      : mName( name )
   {
      mDevice = new Type();
      GameInput::instance().addDevice( mDevice, name );
   }

   /**
    * Removes the device from the input manager and destroys it.
    */
   ~DeviceHandle()
   {
      GameInput::instance().removeDevice( mName );
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
    * The managed device.
    */
   Type* mDevice;
};

} // namespace gk

#endif
