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
 * File:          $RCSfile: BrothaApp.cpp,v $
 * Date modified: $Date: 2002-04-26 12:40:00 $
 * Version:       $Revision: 1.30 $
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
#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdexcept>
#include <memory>
#include "BrothaApp.h"
#include "LoginState.h"

namespace client
{
   BrothaApp::BrothaApp()
      : mCurrentState(0)
      , mTransitionState(0)
      , mLocalPlayer(NULL)
      , mWidth(0)
      , mHeight(0)
      , mSoundMgr(0)
   {
      mCurrentState = new LoginState();

      // init the sound subsystem
      try {
         mSoundMgr = new sound::SoundManager();
         mSoundMgr->getJukebox()->addTrack("music/track1.ogg");
         mSoundMgr->getJukebox()->addTrack("music/track2.ogg");
         mSoundMgr->getJukebox()->play();
      }
      catch (const std::exception& e) {
         std::cerr << "Caught exception " << e.what() << std::endl;
         std::cerr << "Disabling sound!" << std::endl;
      }
   }

   BrothaApp::~BrothaApp() {
      delete mSoundMgr;
   }

   void BrothaApp::update(int elapsedTime) {

      if (mCurrentState) {

         // read all messages from server, and stick them in a field
         // of the application so the state object can read them.
         mServerConnection.readAll(mMsgList);

         mCurrentState->update(this, elapsedTime);

         // if the state invoked a transition, do the switch now
         if (mTransitionState) {
            delete mCurrentState;
            mCurrentState = mTransitionState;
            mTransitionState = 0;
         }
      }

      // update the state of the game
      float dt = float(elapsedTime) / 1000.0f;
      mGame.update(dt);

      // update the jukebox so we can automagically move to the next track
      mSoundMgr->getJukebox()->update();
   }
   
   void BrothaApp::draw() {
      if (mCurrentState) {
         mCurrentState->draw();
      }
/*
      glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
      glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
      glEnable( GL_DEPTH_TEST );
      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

      // set up the projection matrix
      glMatrixMode( GL_PROJECTION );
         glLoadIdentity();
         gluPerspective( 100.0f, (mHeight ? float(mWidth) / mHeight : 0), 0.01f, 1000.0f );

      // initialize your matrix stack used for transforming your models
      glMatrixMode( GL_MODELVIEW );
         glLoadIdentity();

      // Only draw if we're in the game
      if ( isInGame() ) {
         game::Player* player = getLocalPlayer();
         const gmtl::Vec<PRFloat64,3>& pos = player->getObject()->getPosition();

         glColor4f( 1.0, 0.0, 0.0, 1.0f );
         // setup camera
         glTranslatef( pos[0], pos[1], pos[2] );
         /// @todo draw the game!


         // draw grid
         glColor4f(0,0,1,1);
         glBegin( GL_LINES );
         float extent = 1000.0;
         for ( float x = -extent; x < extent; ++x )
         {
            glVertex3f( -extent, 0, x );
            glVertex3f(  extent, 0, x );
            glVertex3f( x, 0, -extent );
            glVertex3f( x, 0,  extent );
         }
         glEnd();

         mScene.draw();
      }
*/
   }
   
   void BrothaApp::resize(int width, int height) {
      mWidth = width;
      mHeight = height;
      glViewport(0, 0, width, height);
   }

   void BrothaApp::onKeyPress(SDLKey sym, bool down)
   {
      if (mCurrentState) {
         mCurrentState->onKeyPress(sym, down);
      }
      return;  /// @todo   put the rest of this stuff in the game state

//      game::Player* player = getLocalPlayer();
      net::UpdatePlayerInfoMessage::UpdateWhat what = net::UpdatePlayerInfoMessage::NOTHING;
      PRFloat64 to = (down ? 1 : 0);

      if (sym == SDLK_w) {
         what = net::UpdatePlayerInfoMessage::ACCELERATION;
      } else if (sym == SDLK_s) {
         what = net::UpdatePlayerInfoMessage::BRAKE;
      } else if (sym == SDLK_SPACE) {
         what = net::UpdatePlayerInfoMessage::HANDBRAKE;
      } else if (sym == SDLK_a) {
         what = net::UpdatePlayerInfoMessage::TURNLEFT;
      } else if (sym == SDLK_d) {
         what = net::UpdatePlayerInfoMessage::TURNRIGHT;
      }

      if(what != net::UpdatePlayerInfoMessage::NOTHING) {
         sendMessage(new net::UpdatePlayerInfoMessage(what, to));
      }

      /*
      

      // test for quit
      if (mQuit.getDigitalData() == gk::DigitalInput::DOWN)
      {
         std::cout<<net::Message::mNumMsgsInMemory<<" Messages leaked"<<std::endl;
         mKernel->shutdown();
      }

      // un/pause game
      if (mPause.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         mGame.setPaused( ! mGame.isPaused() );
      }

      // only deal with player related input if there is a local player
      if ( player != NULL )
      {
         // accelerate
         if (mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         {
            player->setAcceleration( 1 );
         }
         else if (mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_UP)
         {
            player->setAcceleration( 0 );
         }

         // brake
         if (mBrake.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         {
            player->setBrake( 1 );
         }
         else if (mBrake.getDigitalData() == gk::DigitalInput::EDGE_UP)
         {
            player->setBrake( 0 );
         }

         // turn left
         if (mTurnLeft.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         {
            player->setTurnAngle( 1 );
         }
         else if (mTurnLeft.getDigitalData() == gk::DigitalInput::EDGE_UP)
         {
            player->setTurnAngle( 0 );
         }

         // turn right
         if (mTurnRight.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         {
            player->setTurnAngle( 0 );
         }
         else if (mTurnRight.getDigitalData() == gk::DigitalInput::EDGE_UP)
         {
            player->setTurnAngle( -1 );
         }
      }
*/
   }

   void BrothaApp::onMousePress(Uint8 button, bool down, int x, int y) {
      if (mCurrentState) {
         mCurrentState->onMousePress(button, down, x, y);
      }
   }

   void BrothaApp::onMouseMove(int x, int y) {
      if (mCurrentState) {
         mCurrentState->onMouseMove(x, y);
      }
   }

   void BrothaApp::invokeStateTransition(State* state) {
      delete mTransitionState;
      mTransitionState = state;
   }

   void BrothaApp::sendMessage(net::Message* msg) {
      mServerConnection.send(msg);
   }

   void BrothaApp::connectToServer(const std::string& server, int port) {
      mServerConnection.connect(server, port);
   }
}
