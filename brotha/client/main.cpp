/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: main.cpp,v $
 * Date modified: $Date: 2002-03-27 00:51:33 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */
#include <gk/gk.h>   // pull in GameKernel
#include <GL/gl.h>
#include <GL/glu.h>
#include "game/BrothaGame.h"

/**
 * Warn-a-Brotha interface with GameKernel.
 */
class BrothaApp : public gk::AbstractGameApp
{
public:
   BrothaApp( )
      : mKernel( NULL )
   {
   }

   virtual ~BrothaApp( ){
   }


   virtual void onAppInit( gk::IGameKernel* kernel )
   {
      mKernel = kernel;
      mKernel->setName( "Warn-a-Brotha" );
      mQuit.init( "Quit", mKernel );
      mAccelerate.init( "Accelerate", mKernel );
      mBrake.init( "Brake", mKernel );
      mTurnLeft.init( "TurnLeft", mKernel );
      mTurnRight.init( "TurnRight", mKernel );
      mPause.init( "Pause", mKernel );
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

      /// @todo draw the game!
   }

   virtual void onPostFrame()
   {
      Player* player = mGame.getLocalPlayer();

      // test for quit
      if (mQuit.getDigitalData() == gk::DigitalInput::DOWN)
      {
         mKernel->shutdown();
      }

      // accelerate
      if (mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         player->setAccelerate( true );
      }
      else if (mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_UP)
      {
         player->setAccelerate( false );
      }

      // brake
      if (mBrake.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         player->setBrake( true );
      }
      else if (mBrake.getDigitalData() == gk::DigitalInput::EDGE_UP)
      {
         player->setBrake( false );
      }

      // turn left
      if (mTurnLeft.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         player->setTurnLeft( true );
      }
      else if (mTurnLeft.getDigitalData() == gk::DigitalInput::EDGE_UP)
      {
         player->setTurnLeft( false );
      }

      // turn right
      if (mTurnRight.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         player->setTurnRight( true );
      }
      else if (mTurnRight.getDigitalData() == gk::DigitalInput::EDGE_UP)
      {
         player->setTurnRight( false );
      }

      // un/pause game
      if (mPause.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         mGame.setPaused( ! mGame.isPaused() );
      }

      // update the state of the game
      mGame.update();
   }

public:
   gk::AnalogInterface mMouseX, mMouseY;
   gk::DigitalInterface
      mAccelerate,
      mBrake,
      mTurnLeft,
      mTurnRight,
      mPause,
      mQuit;

   gk::IGameKernel* mKernel;

   BrothaGame mGame;
};

int main( int argc, char *argv[] )
{
   // create the kernel and add our app in
   gk::IGameKernel* kernel = gk::createGameKernel(new BrothaApp());
   kernel->config( "config.xml" );
   kernel->run();

   return 0;
}
