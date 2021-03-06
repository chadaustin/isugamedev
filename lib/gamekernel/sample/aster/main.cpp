
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
// Date modified: $Date: 2002-05-14 15:29:18 $
// Version:       $Revision: 1.7 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
// Aster
// asteroids... first person shooter style.
//
// kevin meinert - kevin@vrsource.org
// Public domain
//
// Features:
// - mouselook (no pointer with warp) rotate camera
// - straef
// - air hockey physics
// - alternate keyboard controls (works without mouse)
// - 2 gun turrets on either side...
//
// Usage/Keys:
//
//    see config.xml
//
// TODO:
//   - pretty models and textures... (use a model loader)
//   - keep score
//   - keep track of lives (ships)
//   - die when collide with asteroid (no collision performed yet)
//   - add a top-down 2D map or radar screen
//   - let the top down 2D map be one additional way to play the game
//

#include <gk/gk.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "GameBoard.h"

//////////////////////////////////
// The Aster application
// TODO: make it run more than just a GameBoard: do highscore, and menus too
//////////////////////////////////
class AsterApp : public gk::AbstractGameApp
{
public:
   AsterApp() {}

   virtual ~AsterApp() {}
   
   virtual void onAppInit( gk::IGameKernel* kernel )
   {
      mKernel = kernel;
      gameBoard.init( mKernel );

      stopwatch.pulse();
      mKernel->setName( "Aster" );
      mQuit.init( "Quit", mKernel );
      
      std::cout <<"\n"<<std::flush;
      std::cout <<"aster - by Kevin Meinert - subatomic@vrsource.org \n"<<std::flush;
      std::cout <<" Usage/Keys:                                      \n"<<std::flush;
      std::cout <<"    see config.xml for controls.                  \n"<<std::flush;
      std::cout <<"\n"<<std::flush;
      
      
   }

   virtual void onContextInit()
   {
      //std::cerr << "Inside OnContextInit()..." << std::endl;
   mKernel->setWindowSize( 640, 480 );
      mKernel->showMouse( false );
   }

   /** make opengl calls here.
    *  these calls are usually driven by the game state data that was 
    *  updated by OnPostFrame, use opengl to draw
    */
   virtual void onDraw( int context = 0 )
   {
      //std::cout << "Inside OnDraw()..." << std::endl;
   // get the window params...
      int width, height;
      mKernel->getWindowSize( width, height );
      ::glViewport( 0, 0, width, height );

      ::glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
      ::glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
      ::glEnable( GL_DEPTH_TEST );

      // enable alpha blending..
      ::glEnable( GL_BLEND );
      ::glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

      // set up the projection matrix in the proj stack
      ::glMatrixMode( GL_PROJECTION );
         ::glLoadIdentity();
         ::gluPerspective( 100.0f, width / height, 0.01f, 1000.0f );

      // initialize the other matrix stack we'll use to transform models
      ::glMatrixMode( GL_MODELVIEW );
         ::glLoadIdentity();

      gameBoard.draw();
   }

   /** update your game state data.
    * do your data (non opengl) calculations here 
    */
   virtual void onPreUpdate()
   {
      //std::cout << "Inside OnUpdate()..." << std::endl;
      if (mQuit.getDigitalData() == gk::DigitalInput::DOWN)
      {
         mKernel->shutdown();
         return;
      }
      // update the gameboard      
      stopwatch.pulse();
      mKernel->getWindowSize( gameBoard.width, gameBoard.height );
      gameBoard.update( stopwatch.timeInstant() );
   }

public:
   gk::DigitalInterface mQuit;
   GameBoard gameBoard;
   
   // frame time measurement
   StopWatch stopwatch;
   gk::IGameKernel* mKernel;
};

// aster executable entrypoint...
int main( int argc, char *argv[] )
{
   std::cout<<"Running GameKernel v"<<gk::getVersion()<<std::endl;

   // let our app loose in the Game Kernel
   AsterApp *app = new AsterApp();   
   gk::IGameKernel* kernel = gk::createGameKernel( app );
   if (kernel->config( "config.xml" ))
   {
      kernel->run();
      return 0;
   }
   else
   {
      std::cerr << "Couldn't load config.xml" << std::endl;
   }
   
   return 1;
}
