
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
// File:          $RCSfile: IGameInput.h,v $
// Date modified: $Date: 2003-02-10 05:09:02 $
// Version:       $Revision: 1.5 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_IGAMEINPUT_H
#define GK_IGAMEINPUT_H

#include <gk/gkCommon.h>
#include <gk/DLLInterface.h>
#include <string>

#include <gk/EventInput.h>
#include <gk/IDevice.h>

namespace gk {
class GK_DLL IGameKernel;

/**
 * Interface for the input manager. The input manager is resposible for managing
 * the devices attached to the system and their associated inputs. Additionally,
 * the input manager takes care of dynamically binding an application specific
 * command to a specific input.
 *
 * <p>Applications should generally not use this class directly to get input
 * data. Instead they should rely on the use of InputInterface classes such as
 * DigitalInterface and AnalogInterface to poll the devices for their input.
 *
 * <h3>Example: sampling input</h3>
 * \code
 *    DigitalInterface accelerate;
 *    accelerate.init( "Accelerate" );
 *    if ( accelerate.getDigitalData() == DigitalInput::DOWN ) {
 *       // ... do something ...
 *    }
 * \endcode
 *
 * <p>Of course, this assumes that you have set up your input bindings ...
 *
 * <h3>Example: configuring key bindings
 * \code
 *    gameKernel->getInput()->bind( "Accelerate", "Keyboard", "KEY_UPARROW" );
 *    gameKernel->getInput()->bind( "StrafeLeft", "Keyboard", "KEY_LEFTARROW" );
 *    gameKernel->getInput()->bind( "StrafeRight", "Keyboard", KEY_RIGHTARROW" );
 * \endcode
 *
 * @see AnalogInterface
 * @see DigitalInterface
 */
class GK_DLL IGameInput : public DLLInterface
{
public:
   /**
    * Gets the input that the given alias has been bound to.
    *
    * @param alias      the alias bound to the input
    *
    * @return  the input if alias has been bound, NULL otherwise
    */
   virtual Input* getInput( const std::string& alias ) = 0;

   /**
    * Gets the the Input associated with the <device,input> pair.
    *
    * @param device     the name of the device
    * @param input      the name of the input source on the device
    *
    * @return  the Input if <device,input> has already been bound.
    * @return  NULL if <device,input> has not been bound.
    */
   virtual Input* getInput( const std::string& device,
                            const std::string& input ) = 0;

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
   virtual bool addDevice( IDevice* device, const std::string& name ) = 0;

   /**
    * Gets the device with the given name.
    *
    * @param name    the name of the device to retrieve
    *
    * @return  a pointer to the device if it exists, NULL otherwise
    */
   virtual IDevice* getDevice( const std::string& name ) = 0;

   /**
    * Removes the device with the given name. If no device with the given name
    * is registered, no work is done.
    *
    * @param name    the name of the device to remove
    */
   virtual void removeDevice( const std::string& name ) = 0;

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
   virtual void bind( const std::string& alias, const std::string& device,
                      const std::string& input ) = 0;

   /**
    * Updates all the devices in this input manager. SystemDriver
    * implementations should call this function every frame to ensure valid
    * input within the application.
    *
    * @see IGameKernel
    * @see SystemDriver
    */
   virtual void update() = 0;
};

/**
 * Device wrapper that provides automatic addition and removal of the contained
 * device with the input manager.
 *
 * WARNING: do not change the number of inputs a device has after DeviceHandle has been created.
 *          if you need to, then you must call refresh() to force the GameInput manager to see the new inputs.
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
   DeviceHandle( const std::string& name, IGameKernel* kernel )
      : mName( name ), mKernel( kernel )
   {
      mDevice = new Type();
      IGameInput* input = mKernel->getInput();
      input->addDevice( mDevice, mName );
   }

   /**
    * Creates and instance of the device type and adds it to the input manager.
    *
    * @param name    the name of the device
    * @param kernel  the kernel with which to attach this device to
    * @param dev     the device, device handle assumes ownership of the pointer, and will delete memory for you.
    *
    * @pre kernel != NULL
    */
   DeviceHandle( const std::string& name, IGameKernel* kernel, Type* dev )
      : mName( name ), mKernel( kernel ), mDevice( dev )
   {
      IGameInput* input = mKernel->getInput();
      input->addDevice( mDevice, mName );
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

   /**
    *  remove and re-add the device.
    *  call this when you reconfigure the device inputs 
    *  notifys the GameInput manager to remap bindings.
    */
   void refresh()
   {
      mKernel->getInput()->removeDevice( mName );
      mKernel->getInput()->addDevice( mDevice, mName );
   }

private:
   /**
    * The name of the device.
    */
   std::string mName;

   /**
    * The kernel to which the device is attached.
    */
   IGameKernel* mKernel;

   /**
    * The managed device.
    */
   Type* mDevice;
};

} // namespace gk

#endif
