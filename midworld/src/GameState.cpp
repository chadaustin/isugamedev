/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: GameState.cpp,v $
 * Date modified: $Date: 2002-07-07 03:10:59 $
 * Version:       $Revision: 1.18 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <sstream>
#include "GameState.h"
#include "IntroState.h"
#include "MenuState.h"
#include "Pistol.h"
#include "SpreadGun.h"
#include "Shotgun.h"
#include "AssaultRifle.h"
#include "Application.h"

namespace mw
{
   GameState::GameState( Application* a )
      : State( a )
      , mSpeed(10)
      , mAccelerate(UP)
      , mReverse(UP)
      , mStrafeRight(UP)
      , mStrafeLeft(UP)
      , mShoot(UP)
      , mCycleWeapon(UP)
      , mFPS(0)
      , mFrameCount(0)
      , mFrameTime(0)
      , mMousePosX( a->getWidth() / 2 )
      , mMousePosY( a->getHeight() / 2 )
      , mNeedWarp( true )
   {
      mGunSlots.resize( 10 );
      for (unsigned int x = 0; x < mGunSlots.size(); ++x)
         mGunSlots[x] = UP;
      
      mPlayer.addWeapon( new Pistol );
      mPlayer.addWeapon( new SpreadGun );
      mPlayer.addWeapon( new Shotgun );
      mPlayer.addWeapon( new AssaultRifle );
      for (int i = 0; i < 10; i++)
      {
         mEnemies.push_back(new Enemy());
         gmtl::Point3f inPos(static_cast<float>(5 + i*4), 0, 0);
         mEnemies[i]->setPos(inPos);
         add(mEnemies[i]);
      }
      
      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (mFont)
      {
         std::cout<<"Font font"<<std::endl;
         mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
         if (mFontRenderer)
         {
            std::cout<<"Created renderer"<<std::endl;
            mFontRenderer->setFont(mFont);
         }
      }
   }

   GameState::~GameState()
   {
   }

   void
   GameState::update(float dt)
   {
      // keep track of the mouse cursor...
      if (mNeedWarp)
      {
         ::SDL_WarpMouse( this->application().getWidth() / 2, this->application().getHeight() / 2 );
         mNeedWarp = false;
      }
      
      
      mCamera.setPlayerPos(mPlayer.getPos());

      const gmtl::Vec3f accel(   gmtl::Vec3f(0, 0, -mSpeed)      );
      const gmtl::Vec3f reverse( gmtl::Vec3f(0, 0,  mSpeed*0.7f) );
      const gmtl::Vec3f sleft(   gmtl::Vec3f(-mSpeed*0.9f, 0, 0) );
      const gmtl::Vec3f sright(  gmtl::Vec3f( mSpeed*0.9f, 0, 0) );
      
      // Accelerate
      if (mAccelerate == EDGE_DOWN)
      {
         mPlayerVel += accel;
      }
      else if (mAccelerate == EDGE_UP)
      {
         mPlayerVel -= accel;
      }

      // Reverse
      if (mReverse == EDGE_DOWN)
      {
         mPlayerVel += reverse;
      }
      else if (mReverse == EDGE_UP)
      {
         mPlayerVel -= reverse;
      }

      // Strafe left
      if (mStrafeLeft == EDGE_DOWN)
      {
         mPlayerVel += sleft;
      }
      else if (mStrafeLeft == EDGE_UP)
      {
         mPlayerVel -= sleft;
      }

      // Strafe right
      if (mStrafeRight == EDGE_DOWN)
      {
         mPlayerVel += sright;
      }
      else if (mStrafeRight == EDGE_UP)
      {
         mPlayerVel -= sright;
      }

      // set velocity of player based on the computed inputs
      mPlayer.setVel( mPlayer.getRot() * mPlayerVel );
      
      // Shoot
      if (mShoot == EDGE_DOWN)
      {
         mPlayer.weapon().trigger( true );
         //std::cout<<"Trigger Down"<<std::endl;
      }
      else if (mShoot == EDGE_UP)
      {
         mPlayer.weapon().trigger( false );
         //std::cout<<"Trigger Up"<<std::endl;
      }
      
      if (mCycleWeapon == EDGE_DOWN)
      {
         mPlayer.nextWeapon();
      }      

      for (unsigned int x = 0; x < 9; ++x)
      {
         if (mGunSlots[x] == EDGE_DOWN)
         {
            mPlayer.setWeapon( x );
         }                  
      }
      
      // update player transform
      {
         float screen_size_x = this->application().getWidth();
         float screen_size_y = this->application().getHeight();
         float x = mMousePosX;
         float y = mMousePosY;
         gmtl::Vec3f mid(screen_size_x / 2, screen_size_y / 2, 0);
         gmtl::Vec3f pos( x, y, 0 );
         gmtl::Vec3f dir(pos - mid);
         gmtl::normalize(dir);

         float rad = gmtl::Math::aCos(gmtl::dot(dir, gmtl::Vec3f(1,0,0)));
         gmtl::Vec3f side = gmtl::cross(dir, gmtl::Vec3f(1,0,0));

         // move so it points in mouse dir...
         rad += gmtl::Math::deg2Rad(90.0f);

         // map the dot (angle) and cross (side) to the player
         if (side[2] >= 0.0f)
         {
            float t = rad + gmtl::Math::deg2Rad(180.0f);
            gmtl::Quatf q = gmtl::makeRot<gmtl::Quatf>( gmtl::AxisAnglef( t, 0.0f, 1.0f, 0.0f ) );
            mPlayer.setRot( q );
         }
         else
         {
            float t = -rad;
            gmtl::Quatf q = gmtl::makeRot<gmtl::Quatf>( gmtl::AxisAnglef( t, 0.0f, 1.0f, 0.0f ) );
            mPlayer.setRot( q );
         }
      }
      
      // update edge states...
      updateEdgeState(mAccelerate);
      updateEdgeState(mReverse);
      updateEdgeState(mStrafeRight);
      updateEdgeState(mStrafeLeft);
      updateEdgeState(mShoot);
      updateEdgeState(mCycleWeapon);
      for (unsigned int x = 0; x < mGunSlots.size(); ++x)
         updateEdgeState( mGunSlots[x] );

      // Iterate over all the rigid bodies and update them
      for (RigidBodyList::iterator itr = mBodies.begin(); itr != mBodies.end(); ++itr)
      {
         (*itr)->update(dt);
      }

      mCamera.update( dt );
      mPlayer.update( *this, dt);

      ++mFrameCount;
      mFrameTime += dt;
      if (mFrameTime > 0.5f)
      {
         mFPS = mFrameCount / mFrameTime;
         mFrameCount = 0;
         mFrameTime = 0;
      }
   }

   void GameState::add( RigidBody* b )
   {
      mBodies.push_back( b );
   }
   
   void GameState::draw()
   {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      /// @todo get rid of this...     maybe the clearing buffer too...
      gluPerspective(80.0f, 4.0f/3.0f, 0.01f, 10000.0f);

      // initialize your matrix stack used for transforming your models
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glPushMatrix();
         mCamera.draw();
         mPlayer.draw();
         mScene.draw();

         // Draw all the bodies in the world
         for (RigidBodyList::iterator itr = mBodies.begin(); itr != mBodies.end(); ++itr)
         {
            (*itr)->draw();
         }
      glPopMatrix();

      // draw cursor (dumb)
      glPushMatrix();
      glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         glOrtho(0, this->application().getWidth(), this->application().getHeight(), 0, 300, -300);
      glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glLoadIdentity();
         glTranslatef( mMousePosX, mMousePosY, 0 );
         glScalef( 3.0f, 3.0f, 3.0f );
         cubeGeometry().render();
         glPopMatrix();

         glMatrixMode(GL_PROJECTION);
         glPopMatrix();
      glPopMatrix();
         
      // Draw the HUD
      if (mFontRenderer)
      {
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         glOrtho(0, 640, 480, 0, 1, -1);

         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glLoadIdentity();

         glPushMatrix();
            glTranslatef(20, 20.0f+mFont->getAscent(), 0);
            glColor4f(1,0,0,0.8f);
            mFontRenderer->render("Midworld");
         glPopMatrix();

         glPushMatrix();
            glTranslatef(550, 480 - mFont->getAscent() - mFont->getDescent(), 0);
            glColor4f(1,0,0,1);
            {
               std::stringstream str;
               str << mPlayer.weapon().getAmmoInClip();
               mFontRenderer->render(str.str().c_str());
            }
            glTranslatef(40, 0, 0);
            {
               std::stringstream str;
               str << mPlayer.weapon().getAmmoInBag();
               mFontRenderer->render(str.str().c_str());
            }
         glPopMatrix();

         // FPS
         glPushMatrix();
         glTranslatef(550, 20.0f+mFont->getAscent(), 0);
         glColor4f(1,1,1,1);
         {
            std::stringstream str;
            str << (int)mFPS;
            mFontRenderer->render(str.str().c_str());
         }
         glPopMatrix();

         glPushMatrix();
         glTranslatef(20, 480.0f - mFont->getAscent() - mFont->getDescent(), 0);
         glColor4f(1,0,0,1);
         mFontRenderer->render(mPlayer.weapon().getName().c_str());
         glPopMatrix();

         glPopMatrix();
         glPopMatrix();
      }
   }

   void
   GameState::onKeyPress( SDLKey sym, bool down )
   {
      // todo replace this with a keymapper.
      // map keys to events... yay.
      switch (sym)
      {
      case SDLK_0: updateEdgeState( mGunSlots[0], down ); break;
      case SDLK_1: updateEdgeState( mGunSlots[1], down ); break;
      case SDLK_2: updateEdgeState( mGunSlots[2], down ); break;
      case SDLK_3: updateEdgeState( mGunSlots[3], down ); break;
      case SDLK_4: updateEdgeState( mGunSlots[4], down ); break;
      case SDLK_5: updateEdgeState( mGunSlots[5], down ); break;
      case SDLK_6: updateEdgeState( mGunSlots[6], down ); break;
      case SDLK_7: updateEdgeState( mGunSlots[7], down ); break;
      case SDLK_8: updateEdgeState( mGunSlots[8], down ); break;
      case SDLK_9: updateEdgeState( mGunSlots[9], down ); break;
      case SDLK_w: case SDLK_UP:
         updateEdgeState( mAccelerate, down );
         break;
      case SDLK_s: case SDLK_DOWN:
         updateEdgeState( mReverse, down );
         break;
      case SDLK_a: case SDLK_LEFT:
         updateEdgeState( mStrafeLeft, down );
         break;
      case SDLK_d: case SDLK_RIGHT:
         updateEdgeState( mStrafeRight, down );
         break;
      case SDLK_ESCAPE: case SDLK_q:
         if (down)
         {
            this->invokeTransition( new MenuState( &this->application() ) );
         }
         break;
      }
   }

   void
   GameState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      if (button == SDL_BUTTON_LEFT)
      {
         updateEdgeState(mShoot, down);
         //std::cout<<"LMB "<<down<<std::endl;
      }
      if (button == SDL_BUTTON_RIGHT)
      {
         updateEdgeState(mCycleWeapon, down);
         //std::cout<<"LMB "<<down<<std::endl;
      }
   }

   void
   GameState::onMouseMove(int x, int y)
   {
      // keep track of the game-draw virtual cursor
      mNeedWarp = true;
      x -= this->application().getWidth() / 2;
      y -= this->application().getHeight() / 2;
      mMousePosX += x;
      mMousePosY += y;
      
      // constrain virtual cursor
      if (mMousePosX < 0)
      {
         mMousePosX = 0;
      }
      if (this->application().getWidth() < mMousePosX)
      {
         mMousePosX = this->application().getWidth();
      }
      if (mMousePosY < 0)
      {
         mMousePosY = 0;
      }
      if (this->application().getHeight() < mMousePosY)
      {
         mMousePosY = this->application().getHeight();
      }
   }

   void
   GameState::updateEdgeState(EdgeState& state, bool absoluteState)
   {
      switch (state)
      {
         case DOWN: if (!absoluteState) state = EDGE_UP; break;
         case UP: if (absoluteState) state = EDGE_DOWN; break;
         case EDGE_DOWN: if (absoluteState) state = DOWN; break;
         case EDGE_UP: if (!absoluteState) state = UP; break;
      }
   }

   void
   GameState::updateEdgeState(EdgeState& state)
   {
      switch (state)
      {
         case EDGE_DOWN: state = DOWN; break;
         case EDGE_UP: state = UP; break;
         default: break;
      }
   }
}
