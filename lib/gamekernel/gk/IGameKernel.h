
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
// File:          $RCSfile: IGameKernel.h,v $
// Date modified: $Date: 2003-02-09 07:43:03 $
// Version:       $Revision: 1.9 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_IGAMEKERNEL_H
#define GK_IGAMEKERNEL_H

#include <gk/gkCommon.h>
#include <gk/DLLInterface.h>
#include <gk/IGameApp.h>
#include <gk/IGameInput.h>
#include <gk/ISystemDriver.h>

namespace gk {

/**
 * The IGameKernel interface serves as an effective system platform for a game
 * application. After defining your application object, the GameKernel will
 * drive your application. In the GameKernel system, the IGameKernel instance is
 * the facade for all system driver interactions. An application should deal
 * directly with an instance of this object and never talk directly to an
 * ISystemDriver implementation.
 *
 * <h3>Example: Starting your application</h3>
 * \code
 *    class MyAppType : public gk::AbstractGameApp() {};
 *    int main() {
 *       gk::IGameKernel* kernel = gk::CreateGameKernel( new MyAppType() );
 *       kernel->config( "config.xml" );
 *       kernel->run();
 *       return 0;
 *    }
 * \endcode
 */
class GK_DLL IGameKernel : public DLLInterface
{
public:
   /**
    * Initializes and runs this kernel with the given system driver. If no
    * system driver is specified, GameKernel will try to pick the best
    * available driver. This method will not return until the GameKernel has
    * been shutdown.
    *
    * @param driver     the driver that should underlie the kernel. If driver is
    *                   null, the best available driver will be chosen.
    *
    * @return  true if successful, false otherwise.
    */
   virtual bool run( ISystemDriver* driver = NULL ) = 0;

   /**
    * give a driver name (sdl, glut).  kernel will load the plugin and call it the regName you give.
    */
   virtual bool run( const std::string& driverName, const std::string& regName ) = 0;

   /**
    * Shuts down the application and the system driver. The kernel will stop and
    * the run() call will return. Call this to terminate your application.
    */
   virtual void shutdown() = 0;

   /**
    * Configures this kernel based on the given configuration file.
    *
    * @param file    the name of the configuration file to parse
    *
    * @return  true if successful, false otherwise
    */
   virtual bool config( const char* file ) = 0;

   /**
    * Warps the mouse pointer to the given (x,y) position in your app's window.
    * x and y are relative to your game's open window.
    *
    * @param x    the x position to warp the mouse to
    * @param y    the y position to warp the mouse to
    */
   virtual void warpMouse( int x, int y ) = 0;

   /**
    * Shows or hides the mouse cursor.
    *
    * @param show    true to show the mouse cursor, false to hide it
    */
   virtual void showMouse( bool show ) = 0;

   /**
    * Make the application go fullscreen.
    */
   virtual void fullscreen( int ctx = 0 ) = 0;

   /**
    * Gets the size of your application's window.
    *
    * @param width   filled with the width of the window
    * @param height  filled with the height of the window
    * @param ctx     the context of the window you want to query
    */
   virtual void getWindowSize( int& width, int& height, int ctx = 0 ) = 0;

   /**
    * Sets the size of the window. Use this to restore after a fullscreen or to
    * init the window size in your app's onAppInit().
    *
    * @param width   the new width of the window
    * @param height  the new height of the window
    * @param ctx     the context of the window you want to query
    */
   virtual void setWindowSize( int width, int height, int ctx = 0 ) = 0;

   /**
    * Set the name of the running application. You should call this in
    * onAppInit() with your app's name because some system drivers can't set the
    * window title after onAppInit().
    *
    * @param name    the name of your app
    */
   virtual void setName( const std::string& name ) = 0;

   /**
    * Get the name of the running application.
    *
    * @return  the name of the running application
    */
   virtual const std::string& name() const = 0;

   /**
    * Gets the input manager associated with this kernel.
    *
    * @return  the input manager for this kernel
    */
   virtual IGameInput* getInput() = 0;

   /**
    * Gets the application managed by this kernel.
    *
    * @return the application managed by this kernel
    */
   virtual IGameApp* getApp() = 0;
};

} // namespace gk

#endif
