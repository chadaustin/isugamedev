
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
// File:          $RCSfile: GameKernel.cpp,v $
// Date modified: $Date: 2002-03-22 02:04:27 $
// Version:       $Revision: 1.30 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "GameKernel.h"
#include "GameInput.h"
#include "SystemDriverFactory.h"
#include "GameInputConfigure.h"

namespace gk {

GameKernel::GameKernel( IGameApp* app )
   : mDriver( NULL ), mApp( app )
{
   assert( app != NULL && "You must pass in a valid application" );
   mInput = new GameInput();
}

GameKernel::~GameKernel()
{
   // shutdown the driver and release its memory
   mDriver->shutdown();

   //free memory
   delete mApp;
   delete mInput;
   mApp = NULL;
   mInput = NULL;
}

bool GameKernel::config( const char* file )
{
   return gk::loadInputConfig( std::string(file), this );
}

void GameKernel::warpMouse( int x, int y )
{
   mDriver->warpMouse( x, y );
}

void GameKernel::showMouse( bool show )
{
   mDriver->showMouse( show );
}

/* go fullscreen
 */
void GameKernel::fullscreen( int ctx )
{
   mDriver->fullscreen();
}

/* get the window size */
void GameKernel::getWindowSize( int& width, int& height, int ctx )
{
   mDriver->getWindowSize( width, height, ctx );
}
/* for resize of the window
 * i.e. use this to restore after a full screen
 *      use this to init the window size in onAppInit
 */
void GameKernel::setWindowSize( int width, int height, int ctx )
{
   mDriver->setWindowSize( width, height, ctx );
}

/*
 * gets the input manager instance for this kernel
 */
IGameInput* GameKernel::getInput()
{
   return mInput;
}

void GameKernel::setName( const std::string& name )
{
   mDriver->setName( name );
}

const std::string& GameKernel::name() const
{
   return mDriver->name();
}

bool GameKernel::run( ISystemDriver* driver )
{
   mDriver = driver;
   if ( mDriver == NULL )
   {
      /** @todo pick the best driver for the application */
      SystemDriverFactory::instance().probe( "glut", "GLUT" );
      mDriver = SystemDriverFactory::instance().getDriver( "GLUT" );
   }

   // initialize the driver
   if ( ! mDriver->init( this ) ) {
      std::cout<<"Failed to initialize the system driver."<<std::endl;
      return false;
   }

   // Initialize the registered app before starting the driver in case the app
   // needs to set the window position and name.
   mApp->onAppInit( this );

   // tell the driver to get moving!
   return mDriver->run();
}

void GameKernel::shutdown()
{
   if ( mDriver ) {
      mDriver->shutdown();
      delete mDriver;
      mDriver = NULL;
   }
}

IGameApp* GameKernel::getApp()
{
   return mApp;
}

} // namespace gk
