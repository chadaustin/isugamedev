
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
// File:          $RCSfile: GameKernel.h,v $
// Date modified: $Date: 2002-03-19 01:37:27 $
// Version:       $Revision: 1.25 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEKERNEL_H
#define GK_GAMEKERNEL_H

#include "gk/gkCommon.h"
#include "gk/IGameKernel.h"

namespace gk
{

/**
 * Implementation of the GameKernel interface for usage across a DLL.
 *
 * @see IGameKernel
 */
class GameKernel : public DLLImpl< IGameKernel >
{
public:
   /**
    * Creates a new GameKernel to manage the given application. The kernel will
    * own the memory associated with the app object.
    *
    * @param app  the app to manage with this kernel
    */
   GameKernel( IGameApp* app );

   /**
    * Destroys this GameKernel. This will destroy the application, the system
    * driver and the input manager.
    */
   virtual ~GameKernel();

   /**
    * Initializes and runs this kernel with the given system driver.
    *
    * @param driver     the driver that should underlie the kernel
    *
    * @return  true if successful, false otherwise
    */
   bool startup( ISystemDriver* driver );

   /**
    * Configures this kernel based on the given configuration file.
    *
    * @param file    the name of the configuration file to parse
    *
    * @return  true if successful, false otherwise
    */
   bool config( const char* file );

   /** system shutdown.
    *  exits the system.
    */
   void shutdown();

   /** warp mouse - moves mouse to coord within your app's window.
    *  x and y are relative to your game's open window.
    */
   void warpMouse( int x, int y );

   /** show/hide mouse cursor. */
   void showMouse( bool show );

   /** go fullscreen. */
   void fullscreen( int ctx = 0 );

   /** get the window size */
   void getWindowSize( int& width, int& height, int ctx = 0 );

   /** for resize of the window
    * i.e. use this to restore after a full screen
    *      use this to init the window size in onAppInit
    */
   void setWindowSize( int width, int height, int ctx = 0 );

   /**
    * Adds an application to this kernel. The application will be managed
    * through this kernel. The kernel will own the memory associated with the
    * application
    *
    * @param app     the application to run
    */
   void add( IGameApp* app );

   /**
    * Gets the input manager associated with this kernel.
    *
    * @return  the input manager for this kernel
    */
   GameInput* getInput();

   /** set the name of the running application.
    * you should call this in AppInit with your app's name,
    * because some kernels can't set the window title after AppInit.
    * TODO: consider moving this function to the App baseclass.
    *       this way if more than one app is registered, then
    *       each can be named.
    */
   void setName( const std::string& name );

   /** get the name of the application
    * TODO: consider moving this function to the App baseclass.
    *       this way if more than one app is registered, then
    *       each can be named.
    */
   const std::string& name() const;

   /**
    * Gets the application managed by this kernel.
    *
    * @return the application managed by this kernel
    */
   IGameApp* getApp();

private:
   /**
    * This is the system driver implementation that runs our apps.
    */
   ISystemDriver* mDriver;

   /**
    * The input manager associated with this kernel.
    */
   GameInput* mInput;

   /**
    * The application being managed by this kernel.
    */
   IGameApp* mApp;
};

} // namespace gk

#endif
