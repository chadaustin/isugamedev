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
 * Date modified: $Date: 2002-11-11 05:24:17 $
 * Version:       $Revision: 1.115 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <SDL_opengl.h>
#include <gmtl/Generate.h>
#include <gmtl/QuatOps.h>

#include <loom/command.h>


#include "AmmoCrate.h"
#include "Application.h"
#include "AssaultRifle.h"
#include "BoundsSweepCollisionDetector.h"
#include "CollisionResponse.h"
#include "Enemy.h"
#include "EntityFactory.h"
#include "GameManager.h"
#include "GameState.h"
#include "InputManager.h"
#include "LevelLoader.h"
#include "MissileLauncher.h"
#include "NavNodeTree.h"
#include "OpenSGSceneViewer.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "SpreadGun.h"
#include "StateFactory.h"
#include "StaticEntity.h"
#include "Testing.h"
#include "Turret.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<GameState> creator("Game");
   }

   GameState::GameState(Application* app)
      : State(app)
      , mSpeed(10)
      , mPlayer(this)
      , mFPS(0)
      , mFrameCount(0)
      , mFrameTime(0)
      , mPlayerYawChange(0)
      , mIgnoreMouseMove(true)
   {
      // DO THIS FIRST!!!
      // Tell the EntityFactory to use this as the GameState
      EntityFactory::instance().setGameState(this);
      
      
      // Change the music as appropriate for gaming. :)
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->clear();
      jukebox->addTrack("music/Theme001.ogg");
      jukebox->addTrack("music/Level001.ogg");
      jukebox->addTrack("music/Level002.ogg");
      jukebox->play();
      
      mScene = new Scene();
      OpenSGSceneViewer* viewer = new OpenSGSceneViewer(mScene);
      mSceneViewer = viewer;
      mScene->addSceneListener(viewer);

      // Init the collision detection system
      mCollDet = new BoundsSweepCollisionDetector();
      mCollDet->setSpatialIndex(viewer);

      // Init the physics engine
      mPhysics = new PhysicsEngine(mCollDet, new CollisionResponse(), mScene);

      add(&mPlayer);

      // Initialize the various game subsystems
      initializeInput();

      droidNavTree = new NavNodeTree();
      LevelLoader::load("levels/level1.txt", this);

      mCamera.setMaxFollowDistance(50.0f);
      mCamera.setMinFollowDistance(2.0f);
      
   }

   void
   GameState::update(float dt)
   {
      AI.update();
      mInputManager.update(dt);

      mCamera.setTarget(mPlayer.getPos(), mPlayer.getRot());

      const gmtl::Vec3f accel  (0, 0, -mSpeed);
      const gmtl::Vec3f reverse(0, 0, mSpeed * 0.7f);
      const gmtl::Vec3f sleft  (mSpeed * -0.9f, 0, 0);
      const gmtl::Vec3f sright (mSpeed * 0.9f,  0, 0);

      const float camera_zoom_vel(10.0f);
      const float camera_pitch_vel(gmtl::Math::deg2Rad(100.0f));

      mPlayerVel += accel   * mActionUp->getEdgeState();
      mPlayerVel += reverse * mActionDown->getEdgeState();
      mPlayerVel += sleft   * mActionLeft->getEdgeState();
      mPlayerVel += sright  * mActionRight->getEdgeState();

      // set velocity of player based on the computed inputs
      mPlayer.setVel(mPlayer.getRot() * mPlayerVel);

      // Shoot
      if (mActionShoot->getEdgeState() == 1)
      {                               
         mPlayer.weapon().trigger(true);
      }
      else if (mActionShoot->getEdgeState() == -1)
      {
         mPlayer.weapon().trigger(false);
      }

      if (mActionCycleWeapon->getEdgeState() == 1)
      {
         mPlayer.nextWeapon();
      }

      // Camera zoom in
      if (mActionZoomIn->getEdgeState() == 1)
      {
         mCamera.setFollowDistanceVel(-camera_zoom_vel);
      }
      else if (mActionZoomIn->getEdgeState() == -1)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera zoom out
      if (mActionZoomOut->getEdgeState() == 1)
      {
         mCamera.setFollowDistanceVel(camera_zoom_vel);
      }
      else if (mActionZoomOut->getEdgeState() == -1)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera pitch down
      if (mActionPitchDown->getEdgeState() == 1)
      {
         mCamera.setPitchVel(camera_pitch_vel);
      }
      else if (mActionPitchDown->getEdgeState() == -1)
      {
         mCamera.setPitchVel(0);
      }
      // Camera pitch up
      if (mActionPitchUp->getEdgeState() == 1)
      {
         mCamera.setPitchVel(-camera_pitch_vel);
      }
      else if (mActionPitchUp->getEdgeState() == -1)
      {
         mCamera.setPitchVel(0);
      }
      
      if (mActionQuit->isActive())
      {
         invokeTransition("Menu");
      }

      // update player transform (using mouse-look)
      if (mPlayerYawChange != 0.0f)
      {
         // Update the player's rotation to match the new rotation
         gmtl::Quatf yaw_rot = gmtl::makeRot<gmtl::Quatf>(gmtl::AxisAnglef(
                                       mPlayerYawChange, gmtl::Vec3f(0,1,0)));
         mPlayer.setRot(mPlayer.getRot() * yaw_rot);

         // Reset the yaw change since we took care of it
         mPlayerYawChange = 0.0f;
      }


      // Reap dead entities
      reapDeadEntities();

      // Run the bodies through the physics simulator
      mPhysics->update(dt);

      // Iterate over all the entities and update them
      for (Scene::EntityMapCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         const Entity::UID& uid = itr->first;
         Entity* entity = mScene->get(uid);

         // Allow the entity to update itself
         entity->update(dt);
      }

      // Update the player and the camera
      mCamera.update(dt);
      mPlayer.update(dt);
      
      
      // if the player is below 300, he won!!
      if (mPlayer.getPos()[2] > 300)
      {
         invokeTransition("Ending");
      }
      

      // Update the FPS stat
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
      gluPerspective(80.0f, 4.0f/3.0f, 0.01f, 3000.0f);

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

         drawEntities();

         drawBounds();
      glPopMatrix();

      mHUD.draw(application().getWidth(), application().getHeight(),
                mPlayer, mFPS);
   }
   
   void
   GameState::drawEntities()
   {
      // Run through the entities in the scene and mark those that are dead
      for (Scene::EntityMapCItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         const Entity* entity = itr->second;
         glTranslate(entity->getPos());
         entity->draw();
         glTranslate(-entity->getPos());
      }
   }

   void
   GameState::drawBounds()
   {
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
   }

   void
   GameState::onKeyPress(SDLKey sym, bool down)
   {
      mInputManager.onKeyPress(sym, down);
   }

   void
   GameState::onMousePress(Uint8 button, bool down, int /*x*/, int /*y*/)
   {
      mInputManager.onMousePress(button, down);
   }

   void
   GameState::onMouseMove(int x, int y)
   {
      if (mIgnoreMouseMove)
      {
         mIgnoreMouseMove = false;
         return;
      }

      // Calculate the change in yaw
      gmtl::Point2f wnd_center((float)application().getWidth() / 2.0f,
                               (float)application().getHeight() / 2.0f);
      float yaw = -(float)(x - wnd_center[0]) / 180.0f;
      mPlayerYawChange += yaw;

      // Warp the mouse back to the center of the screen
      SDL_WarpMouse((int)wnd_center[0], (int)wnd_center[1]);
      mIgnoreMouseMove = true;
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
         
         
         if (entity == &mPlayer)
         {
            // if the player is dead, it's Game Over
            invokeTransition("GameOver");
         }
         else
         {
            delete entity;
         }
      }
   }

   void GameState::add(Entity* entity)
   {
      mScene->add(entity);
   }

   void GameState::addSmart(Entity* entity, lm::aiNode *node)
   {
      add(entity);
      AI.registerNode(node);
      mMap[entity->getUID()] = node;
   }

   void
   GameState::addNavNode(Node* node)
   {
      droidNavTree->addNode(node);
   }

   void 
   GameState::addNavNodeLink(std::string n1, std::string n2)
   {
      droidNavTree->addLink(n1, n2);
   }

   void GameState::initializeInput()
   {
      mInputManager.loadMappings("inputmap.cfg");
      mActionUp          = mInputManager.getAction("MOVE UP");
      mActionDown        = mInputManager.getAction("MOVE DOWN");
      mActionRight       = mInputManager.getAction("MOVE RIGHT");
      mActionLeft        = mInputManager.getAction("MOVE LEFT");
      mActionQuit        = mInputManager.getAction("QUIT");
      mActionZoomIn      = mInputManager.getAction("ZOOM IN");
      mActionZoomOut     = mInputManager.getAction("ZOOM OUT");
      mActionPitchUp     = mInputManager.getAction("PITCH UP");
      mActionPitchDown   = mInputManager.getAction("PITCH DOWN");
      mActionYawLeft     = mInputManager.getAction("YAW LEFT");
      mActionYawRight    = mInputManager.getAction("YAW RIGHT");
      mActionShoot       = mInputManager.getAction("SHOOT");
      mActionCycleWeapon = mInputManager.getAction("CYCLE WEAPON");
   }

   /** 
    * this function sets up the turret object in the game, assigns it all the
    * ai related stuff that it needs and returns a reference to the droid.
    * TODO: figure out how to handle the parent case.
    */
   Droid*
   GameState::setupDroid(const std::string& name, const std::string& parent,
                         int maxChild, int level)
   {
      lm::aiNode* node1 = new lm::aiNode(name, NULL, maxChild, level);
      mAInodes.push_back(node1);

      Droid* droid = EntityFactory::instance().create<Droid>();
      node2sCommand = new lm::simpleCommand<Droid>(droid, &Droid::walkRandom);
      myTestCommand = new droidTesting(droid, &mPlayer);
      shootCommand = new droidCommand(droid, &mPlayer);
      
      second = new lm::behavior;
      second->addCommand(node2sCommand);
      second->addCommand(shootCommand);

      node2Instinct = new lm::reflex(node1, second, myTestCommand);
      AI.registerNode(node1);

      mMap[droid->getUID()] = node1;
      
      return droid;
   }
   

   /**
    * This function sets up the turret object in the game, assigns it all the ai
    * related stuff that it needs and returns a reference to that Turret.
    * TODO: figure out how to handle the parent case.
    */
   Turret* 
   GameState::setupTurret(const std::string& name, const std::string& parent,
                          int maxChild, int level)
   {
      lm::aiNode* node1 = new lm::aiNode(name, NULL, maxChild, level);
      mAInodes.push_back(node1);
      
      Turret* turret = EntityFactory::instance().create<Turret>();
      node1sCommand = new lm::simpleCommand<Turret>(turret, &Turret::aim);
      
      first = new lm::behavior;
      first->addCommand(node1sCommand);

      aimTestCommand = new turretTesting(turret, &mPlayer);
      aimCommand = new turretCommand(turret, &mPlayer);

      first->addCommand(aimCommand);

      node1Instinct = new lm::reflex(node1, first, aimTestCommand);
      AI.registerNode(node1);

      mMap[turret->getUID()] = node1;

      return turret;
   }
}
