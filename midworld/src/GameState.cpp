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
 * Date modified: $Date: 2002-10-16 04:57:38 $
 * Version:       $Revision: 1.56 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <fstream>
#include <stdexcept>
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
#include "AmmoCrate.h"

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


      // Change the music as appropriate for gaming. :)
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->clear();
      jukebox->addTrack("music/Theme001.ogg");
      jukebox->addTrack("music/Level001.ogg");
      jukebox->addTrack("music/Level002.ogg");
      jukebox->play();

      mScene = new Scene();
      OpenSGSceneViewer* viewer = new OpenSGSceneViewer(mScene);
//      mSceneViewer = new OpenSGSceneViewer(mScene);
      mSceneViewer = viewer;
      mScene->addSceneListener(mSceneViewer);

      // Init the collision detection system
      mCollDet = new BoundsCollisionDetector();
      mCollDet->setSpatialIndex(viewer);

      // Add the player into the game
      /// XXX: If the player gets reaped it will segfault since mPlayer is a member
      add(&mPlayer);

      // XXX hack for testing aisystem
      appTest = new testing;



      //XXX hack for testing aiNodes for the aiSystem
      node1 = new lm::aiNode("Ben", NULL, -1, 1);
      node2 = new lm::aiNode("Chad", node1, -1, 1);



      Enemy* enemy1 = new Enemy();
      Enemy* enemy2 = new Enemy();
      gmtl::Point3f inPos1(5.0,0.0,-5.0);
      enemy1->setPos(inPos1);
      gmtl::Point3f inPos2(0.0,0.0,-10.0);
      enemy2->setPos(inPos2);



      enemy1->setModel("turret");
      enemy2->setModel("security_droid");

      add(enemy1);
      add(enemy2);


      node1sCommand = new lm::simpleCommand<Enemy>(enemy1, &Enemy::walkRandom);
      node2sCommand = new lm::simpleCommand<Enemy>(enemy2, &Enemy::walkRandom);



      first = new lm::behavior;
      second = new lm::behavior;


      first->addCommand(node1sCommand);
      second->addCommand(node2sCommand);


      //TODO: FOR LOOM: change instincts to take nodes as param1 not
      //instinctMans.
      myTestCommand = new lm::nodeTestCommand<testing>(appTest, &testing::alwaysTrue);

 //     node1Instinct = new lm::instinct(node1->mInstinctManager, first, myTestCommand);

      node2Instinct = new lm::reflex(node2->mReflexManager, second, myTestCommand);

      AI.registerNode(node1);
      AI.registerNode(node2);

      mMap[enemy1->getUID()] = node1;
      mMap[enemy2->getUID()] = node2;



      AmmoCrate* crate = new AmmoCrate();
      crate->setPos(gmtl::Point3f(10, 0, -10));
      crate->setModel("ammo_crate");
      add(crate);

      loadLevel("levels/level1.txt");

      mExplosion = new ParticleEngine("images/explosive_particle.png",
                                      5000, mCamera);
   }

   void
   GameState::update(float dt)
   {
      AI.update();
      mExplosion->update(dt);

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
         Entity* entity = mScene->get(uid);

         // Allow the entity to update itself
         entity->update(dt);

         // Update the physical properties of the entity
         updateDynamics(entity, dt);
      }

      mCamera.update(dt);
      mPlayer.update(*this, dt);

      ++mFrameCount;
      mFrameTime += dt;
      if (mFrameTime > 0.5f)
      {
         mFPS = mFrameCount / mFrameTime;
         mFrameCount = 0;
         mFrameTime = 0;
      }
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
         mGameScene.draw();

         // Make sure we clean up after OpenSG until they fix their bugs
         glPushAttrib(GL_ENABLE_BIT);
         {
            mSceneViewer->draw();
            // Grrr... OpenSG leaves the current texture bound
            glBindTexture(GL_TEXTURE_2D, 0);
         }
         glPopAttrib();

         mExplosion->draw();

         // Draw the bounds
         glColor4f(1,0,0,1);
         for (Scene::EntityMapCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
         {
            const Entity* entity = itr->second;
            const gmtl::AABoxf& bounds = entity->getBounds();
            const gmtl::Point3f& min = bounds.getMin();
            const gmtl::Point3f& max = bounds.getMax();

            // Front face
            glBegin(GL_LINE_LOOP);
               glVertex3f(min[0], min[1], min[2]);
               glVertex3f(max[0], min[1], min[2]);
               glVertex3f(max[0], max[1], min[2]);
               glVertex3f(min[0], max[1], min[2]);
            glEnd();

            // Back face
            glBegin(GL_LINE_LOOP);
               glVertex3f(min[0], min[1], max[2]);
               glVertex3f(max[0], min[1], max[2]);
               glVertex3f(max[0], max[1], max[2]);
               glVertex3f(min[0], max[1], max[2]);
            glEnd();

            // Bottom face
            glBegin(GL_LINE_LOOP);
               glVertex3f(min[0], min[1], min[2]);
               glVertex3f(max[0], min[1], min[2]);
               glVertex3f(max[0], min[1], max[2]);
               glVertex3f(min[0], min[1], max[2]);
            glEnd();

            // Top face
            glBegin(GL_LINE_LOOP);
               glVertex3f(min[0], max[1], min[2]);
               glVertex3f(max[0], max[1], min[2]);
               glVertex3f(max[0], max[1], max[2]);
               glVertex3f(min[0], max[1], max[2]);
            glEnd();
         }
      glPopMatrix();

      mCursor.draw(application().getWidth(), application().getHeight());
      mHUD.draw(application().getWidth(), application().getHeight(),
                mPlayer, mFPS);
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

   void GameState::updateDynamics(Entity* body, float dt)
   {
      // Apply gravity to every body
      body->addForce(PhysicsEngine::GRAVITY * body->getMass());

      float remaining_dt = dt;

      // Keep moving the object until
      while (remaining_dt >= PhysicsEngine::TIME_EPSILON)
      {
         // Update the body for the remaining time differential
         mPhysics.update(body, remaining_dt);

         // Check if the body collided with anything
         gmtl::Vec3f path = body->getNextState().getPos() - body->getCurrentState().getPos();
         CollisionDesc* desc = mCollDet->checkCollision(body, path);

         // No more collisions, let the body update for the remaining distance
         if (!desc)
         {
            body->moveToNextState();

            // Make sure entities never go below the ground.
            // XXX: This is such a hack. We need to get ground collision
            // detection to be done in the collision detector.
            float& y = body->getPos()[1];
            y = std::max(y, 0.0f);

            remaining_dt = 0.0f;
         }
         // There was a collision!
         else
         {
            // Figure out how much time passed to get to the collision. We do this
            // by scaling back the remaining dt by the % of the distance that was
            // travelled.
            float time_to_collision = remaining_dt * desc->getDistance();

            // Update the body to the point of the collision
            mPhysics.update(body, time_to_collision);
            body->moveToNextState();

            // Notify the collider of the collision
            CollisionEvent evt(body, desc);
            body->onCollisionEntry(evt);

            // Notify the collidee of the collision
            Entity* collidee = (Entity*)desc->getCollidee();
            collidee->onCollisionEntry(evt);

            std::cout<<"Collision! "<<body->getUID()<<" -> "<<collidee->getUID()<<std::endl;

            // Update the remaining time differential
            remaining_dt -= time_to_collision;

            // Be good and clean up memory
            delete desc;
         }
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
         mScene->remove(entity);
         NodeMap::iterator itr=mMap.find(entity->getUID());
         // if it's an ai node remove it from the ai system
         if(itr!=mMap.end())
         {
            AI.unregisterNode(itr->second->getName());
         }
         delete entity;
      }
   }

   void GameState::loadLevel(const std::string& filename) {
      std::ifstream in(filename.c_str());
      if (!in.is_open()) {
         throw std::runtime_error("Could not open level file: " + filename);
      }

      std::string type;
      double x, y, z;
      double h, p, r;
      while (in >> type >> x >> y >> z >> h >> p >> r) {
         Entity* e;
         if (type == "droid") {
            e = new Enemy();
            e->setModel("security_droid");
         } else if (type == "crate") {
            e = new AmmoCrate();
            e->setModel("ammo_crate");
         } else {
            throw std::runtime_error("Unknown entity type: " + type);
         }

         e->setPos(gmtl::Point3f(x, y, z));
         e->setRot(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(p, h, r)));
         add(e);
      }
   }

   void GameState::add(Entity* entity)
   {
      mScene->add(entity);
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
