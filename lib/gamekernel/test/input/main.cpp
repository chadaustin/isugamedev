
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
// File:          $RCSfile: main.cpp,v $
// Date modified: $Date: 2002-03-18 05:39:33 $
// Version:       $Revision: 1.14 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////

#include <gk/gk.h>
#include <gk/GameKernel.h>
#include <GlutDriver.h>
#include <gk/SystemDriverFactory.h>
#include "Grid.h"
#include <GL/gl.h>
#include <GL/glu.h>

GK_USING_NAMESPACE

class InputApp : public GameApp
{
public:
   InputApp()
      : mKernel( NULL )
   {
   }

   virtual void onAppInit( IGameKernel* kernel )
   {
      mKernel = kernel;
      mKernel->setName( "Input Test" );
      mQuit.init( "Quit", mKernel );
      mAccelerate.init( "Accelerate", mKernel );
      mMouseX.init( "MouseLookX", mKernel );
      mMouseY.init( "MouseLookY", mKernel );
   }

   virtual void onContextInit()
   {
      mKernel->setWindowSize( 640, 480 );
   }

   virtual void onContextDraw( int context = 0 )
   {
      int width, height;
      mKernel->getWindowSize( width, height );
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

   virtual void onPostFrame()
   {
      if (mQuit.getDigitalData() == DigitalInput::DOWN)
      {
         mKernel->shutdown();
      }

      std::cout<< "Accelerate: "
               << mAccelerate.getDigitalData() << " "
               << " MouseX: " << mMouseX.getAnalogData() << ","
               << mMouseY.getAnalogData() << "\r" << std::flush;
   }

public:
   Grid grid;
   AnalogInterface mMouseX, mMouseY;
   DigitalInterface mAccelerate, mQuit;

   IGameKernel* mKernel;
};

int main( int argc, char *argv[] )
{
   // create the kernel and add our app in
   IGameKernel* kernel = new GameKernel( new InputApp() );

   // configure the system
   loadInputConfig( "config.xml", kernel );

   // create our system driver and let's go!
   SystemDriverFactory::instance().probe( "glut", "GLUT" );
   SystemDriver* driver = SystemDriverFactory::instance().getDriver( "GLUT" );
   kernel->startup( driver );

   return 1;
}
