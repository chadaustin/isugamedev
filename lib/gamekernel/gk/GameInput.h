
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
// Date modified: $Date: 2002-02-07 00:25:18 $
// Version:       $Revision: 1.17 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include "gk/gkCommon.h"
#include <string>
#include <utility> // for pair

#include "gk/Mouse.h"
#include "gk/Keyboard.h"
#include "gk/Singleton.h"

#include "gk/DigitalInput.h"
#include "gk/AnalogInput.h"
#include "gk/EventInput.h"

GK_BEGIN_NAMESPACE

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
 *     GameInput::instance().bind( "StraefLeft", "Keyboard", "KEY_LEFTARROW" );
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
      mKeyboard = new Keyboard();
      mMouse = new Mouse();
      addDevice( mKeyboard, "Keyboard" );
      addDevice( mMouse, "Mouse" );
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
      std::map< std::string, Device* >::const_iterator itr;
      itr = mDevices.find( name );

      if ( itr == mDevices.end() )
      {
         mDevices[ name ] = devPtr;
         return true;
      }
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
      return NULL;
   }

   /**
    *  bind an alias to a device's input
    */
   void bind( const std::string& alias, const std::string& device, const std::string& input )
   {
      Input* in_put = GameInput::instance().getInput( device, input );
      mBindTable[alias].bind( in_put );
   }

// NOTE: the preferred
public:
   /** get the mouse device directly */
   inline const Mouse&        mouse() const { return *mMouse; }

   /** get the mouse device directly */
   inline Mouse&              mouse() { return *mMouse; }

   /** get the keyboard device directly */
   inline const Keyboard&     keyboard() const { return *mKeyboard; }

   /** get the keyboard device directly */
   inline Keyboard&           keyboard() { return *mKeyboard; }

   /** keyboard modifier key. 
    * uh, how to deal with this? you might not want to use ... 
    */
   inline char         modifier() const { return mKeyboardModifier; }

   /** update function.
    * if useing the GameInput manager without GameKernel, you will need to 
    * call this function every frame to ensure valid input
    */
   inline void update()
   {
      keyboard().update();
      mouse().update();
   }
   
private:
   std::map<std::string, EventInput> mBindTable;
   std::map<std::string, Device*> mDevices;
   Mouse*            mMouse;
   Keyboard*         mKeyboard;
   char              mKeyboardModifier;
};

GK_END_NAMESPACE

#endif
