
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
// Date modified: $Date: 2002-03-18 04:19:59 $
// Version:       $Revision: 1.20 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEKERNEL_H
#define GK_GAMEKERNEL_H

#include "gk/gkCommon.h"
#include <vector>

#include "gk/ContextData.h"
#include "gk/GameApp.h"      // the base application type
#include "gk/GameInput.h"
#include "gk/SystemDriver.h"
#include "gk/GameInput.h"

namespace gk
{

/**
 * The GameKernel serves as an effective system platform for a game application.
 * After defining your application object, use the GameKernel to run your
 * application.
 *
 * <h3> "Example (to start your application using GLUT):" </h3>
 * \code
 *    class MyAppType : public gk::GameApp {};
 *    int main()
 *    {
 *       gk::GameKernel* kernel = new gk::GameKernel( new MyAppType() );
 *       gk::SystemDriverFactory::instance().probe( "glut", "GLUT" );
 *       gk::SystemDriver* driver = gk::SystemDriverFactory::instance().getDriver( "GLUT" );
 *       kernel->startup( driver );
 *       return 1;
 *    }
 * \endcode
 *
 * <h3> "Example (to start your application using SDL):" </h3>
 * \code
 *    class MyAppType : public gk::GameApp {};
 *    int main()
 *    {
 *       gk::GameKernel* kernel = new gk::GameKernel( new MyAppType() );
 *       gk::SystemDriverFactory::instance().probe( "sdl", "SDL" );
 *       gk::SystemDriver* driver = gk::SystemDriverFactory::instance().getDriver( "SDL" );
 *       kernel->startup( driver );
 *       return 1;
 *    }
 * \endcode
 *
 * GameKernel is a Facade for all system driver interactions.
 * An application should deal directly with an instance of this object to avoid
 * talking directly to a SystemDriver implementation.
 *
 * @see GameApp
 */
class GameKernel
{
public:
   /**
    * Creates a new GameKernel to manage the given application. The kernel will
    * own the memory associated with the app object.
    *
    * @param app  the app to manage with this kernel
    */
   GameKernel( GameApp* app );

   /**
    * Initializes and runs this kernel with the given system driver.
    *
    * @param driver     the driver that should underlie the kernel
    *
    * @return  true if successful, false otherwise
    */
   bool startup( SystemDriver* driver );

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
   void add( GameApp* app );

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
    */
   GameApp* getApp();

private:
   /**
    * This is the system driver implementation that runs our apps.
    */
   SystemDriver* mDriver;

   /**
    * The input manager associated with this kernel.
    */
   GameInput* mInput;

   /**
    * The application being managed by this kernel.
    */
   GameApp* mApp;
};

} // namespace gk

#endif
