
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
// File:          $RCSfile: SystemDriver.h,v $
// Date modified: $Date: 2002-01-31 06:13:17 $
// Version:       $Revision: 1.4 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef SYSTEMDRIVER_H
#define SYSTEMDRIVER_H

#include "akiCommon.h"
#include <string>

/**
 * Interface to a driver that will run a graphical application. You should
 * generally only get an implementation of this interface through the
 * SystemDriverFactory.
 *
 * @see SystemDriverFactory
 */
class SystemDriver
{
public:
   virtual ~SystemDriver() {}

   /**
    * Initializes this driver and starts it through its main loop.
    *
    * @return  true if successful, false otherwise
    */
   virtual bool startup() = 0;

   /**
    * Destroys this driver and cleans up all memory allocated to it.
    */
   virtual void shutdown() = 0;

   /**
    * Warps the mouse pointer to the given position.
    *
    * @param x       the new x position
    * @param y       the new y position
    */
   virtual void warpMouse( int x, int y ) = 0;

   /**
    * Toggles whether the mouse pointer is shown on the screen.
    *
    * @param show    true to show the cursor, false otherwise
    */
   virtual void showMouse( bool show ) = 0;

   /**
    * Puts the application in fullscreen. To put the application back in a
    * window, use setWindowSize().
    *
    * @param ctx        currently unused - use the default arg
    *
    * @see setWindowSize( int, int, int )
    */
   virtual void fullscreen( int ctx = 0 ) = 0;

   /**
    * Gets the size of the window.
    *
    * @param width   [out]    filled with the width of the window
    * @param height  [out]    filled with the height of the window
    * @param ctx     [in]     currently unused - use the default arg
    */
   virtual void getWindowSize( int& width, int& height, int ctx = 0 ) = 0;

   /**
    * Resizes the window to the given size. Use this to restore after a full
    * screen or to init the window size in onAppInit().
    *
    * @param width      the new width of the window
    * @param height     the new height of the window
    * @param ctx        currently unused - use the default arg
    */
   virtual void setWindowSize( int width, int height, int ctx = 0 ) = 0;

   /**
    * Sets the name to use as the title for the windows.
    *
    * @param name       the name of this kernel
    */
   virtual void setName( const std::string& name ) = 0;

   /**
    * Gets the name to use as the title for the windows.
    *
    * @return  the name used for the window titles
    */
   virtual const std::string& name() const = 0;
};

#endif // ! SYSTEMDRIVER_H
