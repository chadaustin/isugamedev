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
 * Date modified: $Date: 2002-09-06 03:14:21 $
 * Version:       $Revision: 1.27 $
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
#include "BoundsCollisionDetector.h"
#include "Application.h"

#include "Enemy.h"

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
   {
      mCursor.init( a->getWidth(), a->getHeight() );
      mGunSlots.resize( 10 );
      for (unsigned int x = 0; x < mGunSlots.size(); ++x)
         mGunSlots[x] = UP;

      mPlayer.addWeapon( new Pistol );
      mPlayer.addWeapon( new SpreadGun );
      mPlayer.addWeapon( new Shotgun );
      mPlayer.addWeapon( new AssaultRifle );

      // Init the collision detection system
      mSpatialIndex = new VectorSpatialIndex();
      mCollDet = new BoundsCollisionDetector();
      mCollDet->setSpatialIndex(mSpatialIndex);

      // XXX: Hardcoded to add some initial enemies into the game
      for (int i = 0; i < 10; i++)
      {
         Enemy* enemy = new Enemy();
         gmtl::Point3f inPos(static_cast<float>(5 + i*4), 0, 0);
         enemy->setPos(inPos);
         add(enemy);
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
      mCursor.update( this->application().getWidth(),
                      this->application().getHeight() );

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
         float screen_size_x = float(application().getWidth());
         float screen_size_y = float(application().getHeight());
         float x = mCursor.getX();
         float y = mCursor.getY();
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

      // Reap dead entities
      reapDeadEntities();

      // Iterate over all the entities and update them
      for (EntityList::iterator itr = mEntities.begin(); itr != mEntities.end(); ++itr)
      {
         updateDynamics((*itr), dt);
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

   void GameState::updateDynamics(Entity* body, float dt)
   {
      float remaining_dt = dt;
      const gmtl::Vec3f& orig_vel = body->getVel();

      // Check for collisions
      CollisionDesc* desc = mCollDet->checkCollision(body, orig_vel * dt);

      // No more collisions, let the body update the remaining distance
      if (! desc)
      {
         body->update(remaining_dt);
      }
      // We had a collision
      else
      {
         // Figure out how much time passed to get to the collision
         float dist = desc->getDistance();
         float time_to_coll = 0;
         if (orig_vel[0] != 0)
         {
            time_to_coll = dist / orig_vel[0];
         }
         else if (orig_vel[1] != 0)
         {
            time_to_coll = dist / orig_vel[1];
         }
         else if (orig_vel[2] != 0)
         {
            time_to_coll = dist / orig_vel[2];
         }
         else
         {
            time_to_coll = 0;
         }

         // Update the body to the point of the collision
         body->update(time_to_coll);

         // Notify the collider and the collidee of the collision
         CollisionEvent evt(body, desc);
         body->onCollisionEntry(evt);
         Entity* collidee = (Entity*)desc->getCollidee();
         collidee->onCollisionEntry(evt);

         // Stop the body for now
//         body->setVel(gmtl::Vec3f());

         // Be good and clean up our collision desc
         delete desc;
      }
   }

   void GameState::reapDeadEntities()
   {
      for (EntityList::iterator itr = mEntities.begin(); itr != mEntities.end(); )
      {
         Entity* entity = (*itr);
         if (entity->isExpired())
         {
            mSpatialIndex->remove(entity);
            delete entity;
            mEntities.erase(itr);
         }
         else
         {
            ++itr;
         }
      }
   }

   void GameState::add(Entity* entity)
   {
      mEntities.push_back(entity);
      mSpatialIndex->add(entity);
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

         // Draw all the entities in the world
         for (EntityList::iterator itr = mEntities.begin(); itr != mEntities.end(); ++itr)
         {
            (*itr)->draw();
         }
      glPopMatrix();

      mCursor.draw( this->application().getWidth(),
                    this->application().getHeight() );

      // Draw the HUD
      if (mFontRenderer)
      {
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         glOrtho(0, this->application().getWidth(), this->application().getHeight(), 0, 1, -1);

         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glLoadIdentity();

         glPushMatrix();
            glTranslatef(20, 20.0f+mFont->getAscent(), 0);
            glColor4f(1,0,0,0.8f);
            mFontRenderer->render("Midworld");
         glPopMatrix();

         glPushMatrix();
            glTranslatef(550, 480.0f - mFont->getAscent() - mFont->getDescent(), 0);
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
   GameState::onKeyPress(SDLKey sym, bool down)
   {
      // todo replace this with a keymapper.
      // map keys to events... yay.
      switch (sym)
      {
      case SDLK_w: case SDLK_UP:
         updateEdgeState(mAccelerate, down);
         break;
      case SDLK_s: case SDLK_DOWN:
         updateEdgeState(mReverse, down);
         break;
      case SDLK_a: case SDLK_LEFT:
         updateEdgeState(mStrafeLeft, down);
         break;
      case SDLK_d: case SDLK_RIGHT:
         updateEdgeState(mStrafeRight, down);
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
      mCursor.onMouseMove( this->application().getWidth(),
                      this->application().getHeight(), x, y );
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
