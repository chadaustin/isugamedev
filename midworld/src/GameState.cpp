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
 * Date modified: $Date: 2002-10-31 08:35:59 $
 * Version:       $Revision: 1.96 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <SDL_opengl.h>
#include <gmtl/Generate.h>
#include <gmtl/QuatOps.h>

#include "AmmoCrate.h"
#include "Application.h"
#include "AssaultRifle.h"
#include "BoundsCollisionDetector.h"
#include "Enemy.h"
#include "EntityFactory.h"
#include "GameManager.h"
#include "GameState.h"
#include "InputAction.h"
#include "InputBinder.h"
#include "InputParser.h"
#include "InputSymbol.h"
#include "MissileLauncher.h"
#include "OpenSGSceneViewer.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "SpreadGun.h"
#include "StateFactory.h"
#include "StaticEntity.h"
#include "Turret.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<GameState> creator("Game");
   }

   void turretCommand::execute()
   {
      gmtl::Vec3f upVec(0.0, 0.0, 1.0);
      gmtl::Vec3f downVec(0.0,0.0,-1.0);
      gmtl::Quatf currentQuat = mTurret->getRot(); /// Turret's current orientation
      gmtl::Vec3f vecToPlayer = mPlayer->getPos()-mTurret->getPos();
      gmtl::normalize(vecToPlayer);
      gmtl::Quatf mQuat = gmtl::makeRot<gmtl::Quatf>(upVec, vecToPlayer); /// quaternion representing the rotation angle it would take to point at the player.
      gmtl::Quatf finalQuat;  /// the quat that we are actually going to rotate the turret by.
      

      
         
      std::cout << "TimeDelta: " << mTurret->getTimeDelta() << std::endl;
      gmtl::slerp(finalQuat, 0.04f, currentQuat, mQuat);  /// slerp to 7/10 the angle we need to have.
      mTurret->setRot(finalQuat); 
         
      mQuat = gmtl::makeRot<gmtl::Quatf>(downVec, vecToPlayer);
      gmtl::slerp(finalQuat, 1.0f, finalQuat, mQuat);
      gmtl::Vec3f offset(0,0,6);
      mTurret->getGun()->setRot(finalQuat);
      mTurret->getGun()->setPos(mTurret->getPos()+(mTurret->getRot()*offset));
      mTurret->shoot();
    
   }  
   GameState::GameState( Application* a )
      : State( a )
      , mSpeed(10)
      , mPlayer(this)
      , mFPS(0)
      , mFrameCount(0)
      , mFrameTime(0)
      , mPlayerYawChange(0)
      , mIgnoreMouseMove(true)
      , mShoot(UP)
      , mCycleWeapon(UP)
   {
      // DO THIS FIRST!!!
      // Tell the EntityFactory to use this as the GameState
      EntityFactory::instance().setGameState(this);
      
      mGunSlots.resize( 10 );
      for (unsigned int x = 0; x < mGunSlots.size(); ++x)
         mGunSlots[x] = UP;

      mPlayer.addWeapon( new Pistol );
      mPlayer.addWeapon( new SpreadGun );
      mPlayer.addWeapon( new Shotgun );
      mPlayer.addWeapon( new AssaultRifle );
      mPlayer.addWeapon( new MissileLauncher );


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
      mCollDet = new BoundsCollisionDetector();
      mCollDet->setSpatialIndex(viewer);

      // Add the player into the game
      /// XXX: If the player gets reaped it will segfault since mPlayer is a member
      add(&mPlayer);


      // Initialize the various game subsystems
      initializeInput();

      loadLevel("levels/level1.txt");

      mCamera.setMaxFollowDistance(50.0f);
      mCamera.setMinFollowDistance(2.0f);
   }

   void
   GameState::update(float dt)
   {
      AI.update();

      mCamera.setTarget(mPlayer.getPos(), mPlayer.getRot());

      const gmtl::Vec3f accel  (0, 0, -mSpeed);
      const gmtl::Vec3f reverse(0, 0, mSpeed * 0.7f);
      const gmtl::Vec3f sleft  (mSpeed * -0.9f, 0, 0);
      const gmtl::Vec3f sright (mSpeed * 0.9f,  0, 0);

      const float camera_zoom_vel(10.0f);
      const float camera_pitch_vel(gmtl::Math::deg2Rad(100.0f));

      // Accelerate
      if (mActionUp->getState() == EDGE_DOWN)
      {
         mPlayerVel += accel;
      }
      else if (mActionUp->getState() == EDGE_UP)
      {
         mPlayerVel -= accel;
      }

      // Reverse
      if (mActionDown->getState() == EDGE_DOWN)
      {
         mPlayerVel += reverse;
      }
      else if (mActionDown->getState() == EDGE_UP)
      {
         mPlayerVel -= reverse;
      }

      // Strafe left
      if (mActionLeft->getState() == EDGE_DOWN)
      {
         mPlayerVel += sleft;
      }
      else if (mActionLeft->getState() == EDGE_UP)
      {
         mPlayerVel -= sleft;
      }

      // Strafe right
      if (mActionRight->getState() == EDGE_DOWN)
      {
         mPlayerVel += sright;
      }
      else if (mActionRight->getState() == EDGE_UP)
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
      if (mActionZoomIn->getState() == EDGE_DOWN)
      {
         mCamera.setFollowDistanceVel(-camera_zoom_vel);
      }
      else if (mActionZoomIn->getState() == EDGE_UP)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera zoom out
      if (mActionZoomOut->getState() == EDGE_DOWN)
      {
         mCamera.setFollowDistanceVel(camera_zoom_vel);
      }
      else if (mActionZoomOut->getState() == EDGE_UP)
      {
         mCamera.setFollowDistanceVel(0);
      }
      // Camera pitch down
      if (mActionPitchDown->getState() == EDGE_DOWN)
      {
         mCamera.setPitchVel(camera_pitch_vel);
      }
      else if (mActionPitchDown->getState() == EDGE_UP)
      {
         mCamera.setPitchVel(0);
      }
      // Camera pitch up
      if (mActionPitchUp->getState() == EDGE_DOWN)
      {
         mCamera.setPitchVel(-camera_pitch_vel);
      }
      else if (mActionPitchUp->getState() == EDGE_UP)
      {
         mCamera.setPitchVel(0);
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

      // update edge states...
      updateEdgeState(mShoot);
      updateEdgeState(mCycleWeapon);

      // update action states
      updateEdgeState(*mActionUp);
      updateEdgeState(*mActionDown);
      updateEdgeState(*mActionLeft);
      updateEdgeState(*mActionRight);
      updateEdgeState(*mActionZoomIn);
      updateEdgeState(*mActionZoomOut);
      updateEdgeState(*mActionPitchDown);
      updateEdgeState(*mActionPitchUp);
      updateEdgeState(*mActionYawLeft);
      updateEdgeState(*mActionYawRight);

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

      // Update the player and the camera
      mCamera.update(dt);
      mPlayer.update(dt);

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

         drawEntities();

//         drawBounds();
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
      // todo replace this with a keymapper.
      // map keys to events... yay.
      InputBinder* binder = InputBinder::instance();
      InputAction *act = binder->getAction(SDLtoISym(sym));
      if (act == NULL)
      {
         return;
      }

      std::cout << "Got quit action" << std::endl;

      updateEdgeState(*act, down);

      // Quit immediately if requested
      if (act == mActionQuit)
      {
         if (down)
         {
            invokeTransition("Menu");
         }
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
         //std::cout<<"RMB "<<down<<std::endl;
      }
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

   void GameState::updateDynamics(Entity* body, float dt)
   {
      // Apply gravity to every body
      body->addForce(PhysicsEngine::GRAVITY * body->getMass());

      float remaining_dt = dt;

      // Keep moving the object until
      while (remaining_dt >= PhysicsEngine::TIME_EPSILON)
      {
         // Update the body for the remaining time differential
         PhysicsEngine::update(body, remaining_dt);

         // Check if the body collided with anything
         gmtl::Vec3f path = body->getNextState().getPos() - body->getCurrentState().getPos();
         std::auto_ptr<CollisionDesc> desc(
            mCollDet->checkCollision(body, path));

         // No more collisions, let the body update for the remaining distance
         if (!desc.get())
         {
            body->moveToNextState();
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
            PhysicsEngine::update(body, time_to_collision);
            body->moveToNextState();

            // body                == collider
            // desc->getCollidee() == collidee
            mCollisionResponse.collide(body, desc->getCollidee());

            // Update the remaining time differential
            remaining_dt -= time_to_collision;
         }
      }
      
      // Make sure entities never go below the ground.
      // XXX: This is such a hack. We need to get ground collision
      // detection to be done in the collision detector.
      float& y = body->getPos()[1];
      y = std::max(y, 0.0f);
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

   void GameState::loadLevel(const std::string& filename)
   {
      std::ifstream in(filename.c_str());
      if (!in.is_open())
      {
         throw std::runtime_error("Could not open level file: " + filename);
      }

      std::string type;
      double x, y, z;
      double h, p, r;

	  while (in >> type >> x >> y >> z >> h >> p >> r)
      {
         // THIS SUCKS ASS
         // VC++ 7 does not compile this right unless it's static
         // Internal Compiler Error
         // this is not threadsafe
         static Entity* e;

         if (type == "droid")
         {
            std::string name, parent;
            int maxChild, level;
            if(in >> name >> parent >> maxChild >> level)
            {
               Enemy* en;
               en = setupDroid(name, parent, maxChild, level);
               en->setModel("security_droid");
               e = en;
            }
         }
         else if (type == "turret")
         {
            std::string name, parent;
            int maxChild, level;
            if (in >> name >> parent >> maxChild >> level)
            {
               Turret* t;
               t = setupTurret(name, parent, maxChild, level);
               t->setModel("turret");
               e=t;
            }
         }
         else if (type == "ammo")
         {
            e = EntityFactory::instance().create<AmmoCrate>();
            e->setModel("ammo_crate");
         }
         else if (type == "static")
         {
            std::string model;
            if (in >> model)
            {
               e = EntityFactory::instance().create<StaticEntity>();
               e->setModel(model);
            }

            float sx, sy, sz;
            if (in >> sx >> sy >> sz)
            {
               e->setScale(gmtl::Vec3f(sx, sy, sz));
            }
         }
         else if (type == "#")
         {
            // read the rest of the line
            std::string dummy;
            std::getline(in, dummy);
         }
         else
         {
            throw std::runtime_error("Unknown entity type: " + type);
         }

         e->setPos(gmtl::Point3f(x, y, z));
         e->setRot(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
            gmtl::Math::deg2Rad(p),
            gmtl::Math::deg2Rad(h),
            gmtl::Math::deg2Rad(r))));
         add(e);
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


   void GameState::initializeInput()
   {
      InputParser* parser = InputParser::instance();
      parser->parseFile("inputmap.cfg");

      mActionUp = new InputAction();
      parser->bindAction("MOVE UP",    mActionUp);

      mActionDown = new InputAction();
      parser->bindAction("MOVE DOWN",  mActionDown);

      mActionRight = new InputAction();
      parser->bindAction("MOVE RIGHT", mActionRight);

      mActionLeft = new InputAction();
      parser->bindAction("MOVE LEFT",  mActionLeft);

      mActionQuit = new InputAction();
      parser->bindAction("QUIT",       mActionQuit);

      mActionZoomIn = new InputAction();
      parser->bindAction("ZOOM IN",    mActionZoomIn);

      mActionZoomOut = new InputAction();
      parser->bindAction("ZOOM OUT",   mActionZoomOut);

      mActionPitchUp = new InputAction();
      parser->bindAction("PITCH UP",   mActionPitchUp);

      mActionPitchDown = new InputAction();
      parser->bindAction("PITCH DOWN", mActionPitchDown);

      mActionYawLeft = new InputAction();
      parser->bindAction("YAW LEFT",   mActionYawLeft);

      mActionYawRight = new InputAction();
      parser->bindAction("YAW RIGHT",  mActionYawRight);
   }

   /** 
    * this function sets up the turret object in the game, assigns it all the
    * ai related stuff that it needs and returns a reference to the droid.
    * TODO: figure out how to handle the parent case.
    */
   Enemy*
   GameState::setupDroid(std::string name, std::string parent, int maxChild, int level)
   {
      lm::aiNode* node1 = new lm::aiNode(name, NULL, maxChild, level);
      mAInodes.push_back(node1);

      Enemy* enemy = EntityFactory::instance().create<Enemy>();
      node2sCommand = new lm::simpleCommand<Enemy>(enemy, &Enemy::walkRandom);
      myTestCommand = new lm::nodeTestCommand<testing>(appTest, &testing::alwaysTrue);
      
      second = new lm::behavior;
      second->addCommand(node2sCommand);

      node2Instinct = new lm::reflex(node1, second, myTestCommand);
      AI.registerNode(node1);

      mMap[enemy->getUID()] = node1;
      
      return enemy;
   }
   

   /**
    * This function sets up the turret object in the game, assigns it all the ai
    * related stuff that it needs and returns a reference to that Turret.
    * TODO: figure out how to handle the parent case.
    */
   Turret* 
   GameState::setupTurret(std::string name, std::string parent, int maxChild, int level)
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

   void
   GameState::updateEdgeState(InputAction& action, bool absoluteState)
   {
      EdgeState action_state = action.getState();
      updateEdgeState(action_state, absoluteState);
      action.setState(action_state);
   }

   void
   GameState::updateEdgeState(InputAction& action)
   {
      EdgeState action_state = action.getState();
      updateEdgeState(action_state);
      action.setState(action_state);
   }
}
