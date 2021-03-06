
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
// Date modified: $Date: 2002-01-31 06:13:17 $
// Version:       $Revision: 1.7 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef GAMEKERNEL_H
#define GAMEKERNEL_H

#include "akiCommon.h"
#include <vector>
#include <GL/glut.h>                   // gl utility library

#include "ContextData.h"
#include "Singleton.h"
#include "GameApp.h"      // the base application type
#include "GameInput.h"
#include "SystemDriver.h"

/**
 * Facade for all system driver interactions. The application should deal
 * directly with this singleton to avoid talking directly to a SystemDriver
 * implementation.
 */
class GameKernel : public kev::Singleton<GameKernel>
{
public:
   GameKernel();

   /**
    * Initializes and runs this kernel with the given system driver.
    *
    * @param driver     the driver that should underlie the kernel
    *
    * @return  true if successful, false otherwise
    */
   bool startup( SystemDriver* driver );
   void shutdown();

   void warpMouse( int x, int y );
   void showMouse( bool show );

   /* go fullscreen
    */
   void fullscreen( int ctx = 0 );

   /* get the window size */
   void getWindowSize( int& width, int& height, int ctx = 0 );

   /* for resize of the window
    * i.e. use this to restore after a full screen
    *      use this to init the window size in OnAppInit
    */
   void setWindowSize( int width, int height, int ctx = 0 );

   void setName( const std::string& name );

   const std::string& name() const;

   std::vector<GameApp*>& applications();

private:
   /**
    * This is the system driver implementation that runs our apps.
    */
   SystemDriver* mDriver;
};

// create an instance of this type to register your application
// delete it to unregister it.
template< class applicationType >
class GameKernelRegister
{
public:
   GameKernelRegister() : mApplication()
   {
      GameKernel::instance().applications().push_back( &mApplication );
      int size = GameKernel::instance().applications().size();
   }
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

   applicationType mApplication;
};

#endif
