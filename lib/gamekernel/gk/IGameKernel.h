
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
// Date modified: $Date: 2002-03-18 06:34:55 $
// Version:       $Revision: 1.2 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_IGAMEKERNEL_H
#define GK_IGAMEKERNEL_H

#include <gk/gkCommon.h>
#include <gk/DLLInterface.h>
#include <gk/IGameApp.h>
#include <gk/GameInput.h>
#include <gk/SystemDriver.h>

namespace gk {

/**
 * The IGameKernel interface serves as an effective system platform for a game
 * application. After defining your application object, the GameKernel will
 * drive your application. In the GameKernel system, the IGameKernel instance is
 * the facade for all system driver interactions. An application should deal
 * directly with an instance of this object and never talk directly to a
 * SystemDriver implementation.
 *
 * <h3>Example: Starting your application</h3>
 * \code
 *    class MyAppType : public gk::AbstractGameApp() {};
 *    int main() {
 *       gk::IGameKernel* kernel = gk::CreateGameKernel( new MyAppType() );
 *       gk::loadInputConfig( "config.xml", kernel );
 *       kernel->startup();
 *       return 0;
 *    }
 * \endcode
 */
class IGameKernel : public Private::DLLInterface
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
   virtual bool startup( SystemDriver* driver = NULL ) = 0;

   /**
    * Shuts down the application and the system driver. The kernel will stop and
    * the startup() call will return. Call this to terminate your application.
    */
   virtual void shutdown() = 0;

   /**
    * Warps the mouse pointer to the given (x,y) position in your app's window.
    * x and y are relative to your game's open window.
    */
   virtual void warpMouse( int x, int y ) = 0;

   /**
    * Show/hide the mose cursor.
    */
   virtual void showMouse( bool show ) = 0;

   /**
    * Make the application go fullscreen.
    */
   virtual void fullscreen( int ctx = 0 ) = 0;

   /**
    * Gets the size of your app's window.
    */
   virtual void getWindowSize( int& width, int& height, int ctx = 0 ) = 0;

   /**
    * Sets the size of the window. Use this to restore after a fullscrreen or to
    * init the window size in your app's onAppInit().
    */
   virtual void setWindowSize( int width, int height, int ctx = 0 ) = 0;

   /**
    * Set the name of the running application. You should call this in
    * onAppInit() with your app's name because some system drivers can't set the
    * window title after onAppInit().
    * 
    * @todo consider moving this function to the App baseclass.
    *       this way if more than one app is registered, then
    *       each can be named.
    */
   virtual void setName( const std::string& name ) = 0;

   /**
    * Get the name of the application.
    *
    * @todo consider moving this function to the App baseclass.
    *       this way if more than one app is registered, then
    *       each can be named.
    */
   virtual const std::string& name() const = 0;

   /**
    * Gets the input manager associated with this kernel.
    *
    * @return  the input manager for this kernel
    */
   virtual GameInput* getInput() = 0;

   /**
    * Gets the application managed by this kernel.
    *
    * @return the application managed by this kernel
    */
   virtual IGameApp* getApp() = 0;
};
   
} // namespace gk

#endif
