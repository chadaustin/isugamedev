
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
// Date modified: $Date: 2002-02-11 01:53:43 $
// Version:       $Revision: 1.12 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GK_GAMEKERNEL_H
#define GK_GAMEKERNEL_H

#include "gk/gkCommon.h"
#include <vector>
#include <GL/glut.h>                   // gl utility library

#include "gk/ContextData.h"
#include "gk/Singleton.h"
#include "gk/GameApp.h"      // the base application type
#include "gk/GameInput.h"
#include "gk/SystemDriver.h"

namespace gk 
{

/**
 * The GameKernel serves as an effective system platform for a game application.
 * After defining your application object, use the GameKernel to run your 
 * application.
 * 
 * <h3> "Example (to start your application using GLUT):" </h3>
 * \code
 *    class MyApplicationType : public gk::GameApp {};
 *    int main()
 *    {
 *       gk::GameKernelRegister<MyApplicationType> reg;
 *       gk::SystemDriver* driver = new gk::GlutDriver();
 *       gk::GameKernel::instance().startup( driver );
 *       return 1;
 *    }
 * \endcode
 *
 * <h3> "Example (to start your application using SDL):" </h3>
 * \code
 *    class MyApplicationType : public gk::GameApp {};
 *    int main()
 *    {
 *       gk::GameKernelRegister<MyApplicationType> reg;
 *       gk::SystemDriver* driver = new gk::SdlDriver();
 *       gk::GameKernel::instance().startup( driver );
 *       return 1;
 *    }
 * \endcode
 *
 * GameKernel is a Facade for all system driver interactions. 
 * An application should deal directly with this singleton to avoid talking 
 * directly to a SystemDriver implementation.
 * 
 * @see GameApp
 * @see GameKernelRegister
 * @see Singleton
 */
class GameKernel : public Singleton<GameKernel>
{
public:
   /** constructor */
   GameKernel();

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
    *      use this to init the window size in OnAppInit
    */
   void setWindowSize( int width, int height, int ctx = 0 );

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

   /** what applications are registered. */
   std::vector<GameApp*>& applications();

private:
   /**
    * This is the system driver implementation that runs our apps.
    */
   SystemDriver* mDriver;
};

/** registers a new application of type applicationType with the GameKernel.
 * create an instance of this class to register your application.
 * delete it to unregister it.
 *
 * <h3> "Example (to create and register your application with the kernel):" </h3>
 * \code
 *    class MyApplicationType : public gk::GameApp {};
 *    gk::GameKernelRegister<MyApplicationType> reg;
 * \endcode
 *
 * @see GameKernel
 */
template< class applicationType >
class GameKernelRegister
{
public:
   /** registers a new application of type applicationType with the GameKernel.
    */
   GameKernelRegister() : mApplication()
   {
      GameKernel::instance().applications().push_back( &mApplication );
   }

   /** unregisters the application from the GameKernel. */
   virtual ~GameKernelRegister()
   {

      std::vector<GameApp*>::iterator it;
      for (it = GameKernel::instance().applications().begin();
           it != GameKernel::instance().applications().end();
           ++it)
      {
         if (&mApplication == (*it))
         {
            GameKernel::instance().applications().erase( it );
            return;
         }
      }

      // if not found, then the list probably was deallocated
      // (because application exited)
      // whatever, there wont be any dangling memory anyway.
   }
private:
   applicationType mApplication;
};

} // namespace gk

#endif
