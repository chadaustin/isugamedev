
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
// File:          $RCSfile: aki.cpp,v $
// Date modified: $Date: 2002-01-31 16:20:10 $
// Version:       $Revision: 1.15 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#include "GameApp.h"      // the base application type
#include "GameKernel.h"
#include "GameInput.h"
#include "GameInputConfigure.h"
#include "AnalogInterface.h"
#include "DigitalInterface.h"
#include "GlutDriver.h"
#include "Grid.h"

class AkiGame : public GameApp
{
public:
   virtual void OnAppInit()
   {
      GameKernel::instance().setName( "Aki's Quest" );
      mQuit.init( "Quit" );
      mAccelerate.init( "Accelerate" );
      mMouseX.init( "MouseLookX" );
      mMouseY.init( "MouseLookY" );
   }

   virtual void OnContextInit()
   {
      GameKernel::instance().setWindowSize( 640, 480 );
   }

   virtual void OnContextDraw( int context = 0 )
   {
      int width, height;
      GameKernel::instance().getWindowSize( width, height );
      glViewport( 0, 0, width, height );

      glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
      glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
      glEnable( GL_DEPTH_TEST );
      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


      // set up the projection matrix
      glMatrixMode( GL_PROJECTION );
         glLoadIdentity();
         gluPerspective( 100.0f, width / height, 0.01f, 1000.0f );

      // initialize your matrix stack used for transforming your models
      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();

      glTranslatef( 0, -4, 0 );
      grid.draw();
   }

   virtual void OnPostFrame()
   {
      if (mQuit.getDigitalData() == DigitalInput::DOWN)
      {
         GameKernel::instance().shutdown();
      }

      std::cout<< "Accelerate: "
               << mAccelerate.getDigitalData() << " "
               << " MouseX: " << mMouseX.getAnalogData() << ","
               << mMouseY.getAnalogData() << std::endl;
   }

public:
   Grid grid;
   AnalogInterface mMouseX, mMouseY;
   DigitalInterface mAccelerate, mQuit;
};

int main( int argc, char *argv[] )
{
   gk::loadInputConfig( "config.xml" );
   GameKernelRegister<AkiGame> reg;
   SystemDriver* driver = new GlutDriver();
   GameKernel::instance().startup( driver );
   return 0;
}

// Support people who create Win32 application projects in VC6
#ifdef _WIN32
#ifndef _CONSOLE

int WINAPI WinMain(
      HINSTANCE /*instance*/,
      HINSTANCE /*prevInstance*/,
      LPSTR /*commandLine*/,
      int /*showCommand*/ )
{
   return main( __argc, __argv );
}

#endif // ! _CONSOLE
#endif // _WIN32
