
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
// Date modified: $Date: 2002-02-09 21:54:44 $
// Version:       $Revision: 1.17 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "gk/GameKernel.h"

namespace gk {

GameKernel::GameKernel()
   : mDriver( NULL )
{
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
 *      use this to init the window size in OnAppInit
 */
void GameKernel::setWindowSize( int width, int height, int ctx )
{
   mDriver->setWindowSize( width, height, ctx );
}

void GameKernel::setName( const std::string& name )
{
   mDriver->setName( name );
}

const std::string& GameKernel::name() const
{
   return mDriver->name();
}

std::vector<GameApp*>& GameKernel::applications()
{
   static std::vector<GameApp*> registered_applications;
   return registered_applications;
}

bool GameKernel::startup( SystemDriver* driver )
{
   assert( (driver != NULL) && "you must pass in a valid system driver!" );
   assert( applications().size() > 0 && "you must register at least one application" );

   // keep a copy of our system driver
   mDriver = driver;

   // initialize the driver
   if ( ! mDriver->init() ) {
      std::cout<<"Failed to initialize the system driver."<<std::endl;
      return false;
   }

   //Initialize all registered applications, do this before initing glut, in case app
   // needs to set window position and name.
   unsigned int x;
   for (x = 0; x < applications().size(); ++x)
   {
      assert( applications()[x] != NULL && "you registered a NULL application" );
      applications()[x]->OnAppInit();
   }

   // tell the driver to get moving!
   return mDriver->run();
}

void GameKernel::shutdown()
{
   mDriver->shutdown();
   delete mDriver;
   mDriver = NULL;
}

} // namespace gk
