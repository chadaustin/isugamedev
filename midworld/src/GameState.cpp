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
 * Date modified: $Date: 2002-10-01 04:26:42 $
 * Version:       $Revision: 1.37 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <sstream>
#include <SDL_opengl.h>
#include "GameState.h"
#include "StateFactory.h"
#include "Pistol.h"
#include "SpreadGun.h"
#include "Shotgun.h"
#include "AssaultRifle.h"
#include "BoundsCollisionDetector.h"
#include "Application.h"
#include "OpenSGSceneViewer.h"
#include "GameManager.h"

#include "Enemy.h"


namespace mw
{
   namespace
   {
      StateCreatorImpl<GameState> creator("Game");
   }

   GameState::GameState( Application* a )
      : State( a )
      , mSpeed(10)
      , mAccelerate(UP)
      , mReverse(UP)
      , mStrafeRight(UP)
      , mStrafeLeft(UP)
      , mShoot(UP)
      , mCycleWeapon(UP)
      , mCameraZoomIn(UP)
      , mCameraZoomOut(UP)
      , mCameraPitchDown(UP)
      , mCameraPitchUp(UP)
      , mCameraYawLeft(UP)
      , mCameraYawRight(UP)
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


      // Init some of the model resources
      ResourceManager* res_mgr = GameManager::instance().getResourceManager();
      res_mgr->add("security_droid", "models/security_droid.obj");
      res_mgr->add("bullet",         "models/bullet.obj");
      res_mgr->add("casing",         "models/casing.obj");

      // Init the collision detection system
      mSpatialIndex = new VectorSpatialIndex();
      mCollDet = new BoundsCollisionDetector();
      mCollDet->setSpatialIndex(mSpatialIndex);

      mScene = new Scene();
      mSceneViewer = new OpenSGSceneViewer(mScene);
      mScene->addSceneListener(mSceneViewer);

      // XXX: Hardcoded to add some initial enemies into the game
      for (int i = 0; i < 10; i++)
      {
         Enemy* enemy = new Enemy();
         enemy->setPos(gmtl::Point3f(5 + i * 4, 0, 0));
         enemy->setModel("security_droid");
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
      /// @todo  Do we really need this?
      ResourceManager* res_mgr = GameManager::instance().getResourceManager();
      res_mgr->remove("security_droid");
      res_mgr->remove("bullet");
      res_mgr->remove("casing");
   }

   void
   GameState::update(float dt)
   {
      mCursor.update(application().getWidth(),
                     application().getHeight());

      mCamera.setTarget(mPlayer.getPos(), gmtl::Quatf());
//      mCamera.setTarget(mPlayer.getPos(), mPlayer.getRot());

      const gmtl::Vec3f accel  (0, 0, -mSpeed);
      const gmtl::Vec3f reverse(0, 0, mSpeed * 0.7f);
      const gmtl::Vec3f sleft  (mSpeed * -0.9f, 0, 0);
      const gmtl::Vec3f sright (mSpeed * 0.9f,  0, 0);

      const float camera_zoom_vel(10.0f);
      const float camera_pitch_vel(gmtl::Math::deg2Rad(100.0f));
      const float camera_yaw_vel(gmtl::Math::deg2Rad(100.0f));

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
      mPlayer.setVel(mPlayer.getRot() * mPlayerVel);

      // Shoot
      if (mShoot == EDGE_DOWN)
      {
         mPlayer.weapon().trigger( true );
      }
      else if (mShoot == EDGE_UP)
      {
         mPlayer.weapon().trigger( false );
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

      // Camera zoom in
      if (mCameraZoomIn == EDGE_DOWN)
      {
         mCamera.setFollowDistanceVel(-camera_zoom_vel);
      }
      else if (mCameraZoomIn == EDGE_UP)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera zoom out
      if (mCameraZoomOut == EDGE_DOWN)
      {
         mCamera.setFollowDistanceVel(camera_zoom_vel);
      }
      else if (mCameraZoomOut == EDGE_UP)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera pitch down
      if (mCameraPitchDown == EDGE_DOWN)
      {
         mCamera.setPitchVel(camera_pitch_vel);
      }
      else if (mCameraPitchDown == EDGE_UP)
      {
         mCamera.setPitchVel(0);
      }
      // Camera pitch up
      if (mCameraPitchUp == EDGE_DOWN)
      {
         mCamera.setPitchVel(-camera_pitch_vel);
      }
      else if (mCameraPitchUp == EDGE_UP)
      {
         mCamera.setPitchVel(0);
      }
      // Camera yaw left
      if (mCameraYawLeft == EDGE_DOWN)
      {
         mCamera.setYawVel(camera_yaw_vel);
      }
      else if (mCameraYawLeft == EDGE_UP)
      {
         mCamera.setYawVel(0);
      }
      // Camera yaw right
      if (mCameraYawRight == EDGE_DOWN)
      {
         mCamera.setYawVel(-camera_yaw_vel);
      }
      else if (mCameraYawRight == EDGE_UP)
      {
         mCamera.setYawVel(0);
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
      updateEdgeState(mCameraZoomIn);
      updateEdgeState(mCameraZoomOut);
      updateEdgeState(mCameraPitchDown);
      updateEdgeState(mCameraPitchUp);
      updateEdgeState(mCameraYawLeft);
      updateEdgeState(mCameraYawRight);

      for (unsigned int x = 0; x < mGunSlots.size(); ++x)
         updateEdgeState( mGunSlots[x] );

      // Reap dead entities
      reapDeadEntities();

      // Iterate over all the entities and update them
      for (Scene::EntityMapCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         const Entity::UID& uid = itr->first;
         updateDynamics(mScene->get(uid), dt);
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

      // Apply gravity to every body
      body->addForce(gmtl::Vec3f(0, -9.81f, 0) * body->getMass());

      // Check for collisions
      CollisionDesc* desc = mCollDet->checkCollision(body, orig_vel * dt);

      // No more collisions, let the body update the remaining distance
      if (!desc)
      {
         body->update(remaining_dt);

         // Make sure entities never go below the ground.
         float& y = body->getPos()[1];
         y = std::max(y, 0.0f);
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
      typedef std::list<Entity::UID> UIDList;
      UIDList dead;

      // Run through the entities in the scene and mark those that are dead
      for (Scene::EntityMapCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         const Entity::UID& uid = itr->first;
         const Entity* entity = itr->second;
         if (entity->isExpired())
         {
            dead.push_back(uid);
         }
      }

      // Remove all entities marked as dead
      for (UIDList::iterator itr = dead.begin(); itr != dead.end(); ++itr)
      {
         Entity* entity = mScene->get(*itr);
         mSpatialIndex->remove(entity);
         mScene->remove(entity);
         delete entity;
      }
   }

   void GameState::add(Entity* entity)
   {
      mScene->add(entity);
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
         mGameScene.draw();
         mSceneViewer->draw();
      glPopMatrix();

      mCursor.draw(application().getWidth(), application().getHeight());

      // Draw the HUD
      if (mFontRenderer)
      {
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         glOrtho(0, application().getWidth(), application().getHeight(), 0, 1, -1);

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
            this->invokeTransition("Menu");
         }
         break;
      case SDLK_KP9:
         updateEdgeState(mCameraZoomIn, down);
         break;
      case SDLK_KP3:
         updateEdgeState(mCameraZoomOut, down);
         break;
      case SDLK_KP8:
         updateEdgeState(mCameraPitchDown, down);
         break;
      case SDLK_KP2:
         updateEdgeState(mCameraPitchUp, down);
         break;
      case SDLK_KP4:
         updateEdgeState(mCameraYawLeft, down);
         break;
      case SDLK_KP6:
         updateEdgeState(mCameraYawRight, down);
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
      mCursor.onMouseMove(
         application().getWidth(),
         application().getHeight(),
         x, y);
   }

   void
   GameState::updateEdgeState(EdgeState& state, bool absoluteState)
   {
      switch (state)
      {
         case DOWN:      if (!absoluteState) state = EDGE_UP;   break;
         case UP:        if (absoluteState)  state = EDGE_DOWN; break;
         case EDGE_DOWN: if (absoluteState)  state = DOWN;      break;
         case EDGE_UP:   if (!absoluteState) state = UP;        break;
      }
   }

   void
   GameState::updateEdgeState(EdgeState& state)
   {
      switch (state)
      {
         case EDGE_DOWN: state = DOWN; break;
         case EDGE_UP:   state = UP;   break;
         default: break;
      }
   }
}
