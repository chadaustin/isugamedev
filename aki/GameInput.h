
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
// Date modified: $Date: 2002-01-30 17:28:54 $
// Version:       $Revision: 1.11 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////

#ifndef GAMEINPUT
#define GAMEINPUT

#include <string>
#include <utility> // for pair

#include "Mouse.h"
#include "Keyboard.h"
#include "Singleton.h"

#include "DigitalInput.h"
#include "AnalogInput.h"
#include "EventInput.h"

/** 
 * Input manager for game input. 
 * Try to use the Interface classes instead of this class directly
 * (i.e. use DigitalInterface or AnalogInterface)
 *
 * <h3> "Usage (to sample input):" </h3>
 * \code
 *    DigitalInterface accelerate;
 *    accelerate.init( "Accelerate" );
 *    if (accelerate.getDigitalData() == DigitalInput::DOWN)
 *       ... do something ...
 * \endcode
 *
 * <h3>  "Usage (to configure):" </h3>
 * \code
 *     GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_UPARROW" );
 *     GameInput::instance().bind( "StraefLeft", "Keyboard", "KEY_LEFTARROW" );
 *     GameInput::instance().bind( "Accelerate", "Keyboard", "KEY_RIGHTARROW" );
 * \endcode
 *
 * @see DigitalInterface
 * @see AnalogInterface
 * @see kev::Singleton<GameInput>
 * @author Kevin Meinert <kevin@vrsource.org>
 * @author other happy people...
 */
class GameInput : public kev::Singleton<GameInput>
{
public:
   GameInput()
   {
      mDevices["Keyboard"] = mKeyboard = new Keyboard;
      mDevices["Mouse"] = mMouse = new Mouse;
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

   /** Add a device to InputManager.
    *
    * Add the devPtr to the device Array, devPtr should
    * not already be in the array.  Returns -1 on failure
    *
    * MODIFIES: self
    */
   bool addInput( Input* devPtr );

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

private:
   std::map<std::string, EventInput> mBindTable;
   std::map<std::string, Device*> mDevices;
   Mouse*            mMouse;
   Keyboard*         mKeyboard;
   char              mKeyboardModifier;
};

#endif
