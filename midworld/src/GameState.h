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
 * File:          $RCSfile: GameState.h,v $
 * Date modified: $Date: 2002-10-29 18:57:32 $
 * Version:       $Revision: 1.51 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_GAME_STATE_H
#define MW_GAME_STATE_H

#include <vector>

#include <loom/aiSystem.h>
#include <loom/reflex.h>
#include <loom/behavior.h>
#include <loom/unit.h>
#include <loom/command.h>

#include <gmtl/Point.h>
#include <gmtl/LineSeg.h>
#include <gmtl/Generate.h>
//#include <gmtl/QuatOps.h>

#include <SDL.h>
#include "Camera.h"
#include "CollisionDetector.h"
#include "Cursor.h"
#include "Entity.h"
#include "GameScene.h"
#include "HUD.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Scene.h"
#include "SceneViewer.h"
#include "InputAction.h"
#include "State.h"
#include "Turret.h"
#include "ParticleEngine.h"

namespace mw
{

   class Application;

   class turretTesting : public lm::testing
   {
   public:
      turretTesting(Turret* t, Player* p)
      {
         mTurret = t;
         mPlayer = p;
      }


      virtual bool test()
      {
         gmtl::Point3f pos1, pos2;
         pos1 = mTurret->getPos();
         pos2 = mPlayer->getPos();
         gmtl::LineSegf dist(pos1, pos2);
         if(dist.getLength() < 20)
            return true;
         else
            return false;
      }
   private:
      Turret* mTurret;
      Player* mPlayer;

   };


   class turretCommand : public lm::command
   {
      public:

      turretCommand(Turret* t, Player* p)
      {
         mTurret = t;
         mPlayer = p;
      }

      virtual void execute();
         



      private:
         Turret* mTurret;
         Player* mPlayer;
   };



   class testing
   {
   public:
      testing() {}

      bool alwaysTrue()
      {
         return true;
      }
      bool alwaysFalse()
      {
         return false;
      }
      bool aimTrue()
      {
      }
   private:
   };


   /**
    * The state in which the game is played.
    */
   class GameState : public State
   {
   public:
      GameState( Application* a );

      void update(float dt);
      void draw();
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      /**
       * Adds an entity into the world.
       *
       * @param entity     the entity to add into the world
       */
      void add(Entity* entity);

      /**
       * Adds a "smart" entity into the world.
       * A smart entity is an entity that is also
       * a loom node.
       *
       * @param entity     the entity to add into the world
       * @param node       the lm::aiNode representation of the entity
       */
      virtual void addSmart(Entity* entity, lm::aiNode *node);

      /**
       * Get the player
       */
      Player& getPlayer()
      {
         return mPlayer;
      }
      
      Camera& getCamera()
      {
         return mCamera;
      }

   private:
      void initializeInput();
      void initializeAI();
      
      void drawEntities();

      /// Called on input change
      void updateEdgeState(EdgeState& state, bool absoluteState);
      void updateEdgeState(InputAction& action, bool absoluteState);

      /// Called on update for each button
      void updateEdgeState(EdgeState& state);
      void updateEdgeState(InputAction& action);

      /**
       * Updates the dynamics of the given rigid body over the given time
       * differential.
       *
       * @param body       the body whose dynamics will be updated
       * @param dt         the time differential in seconds
       */
      void updateDynamics(Entity* body, float dt);

      /**
       * Deletes and removes from the game all entities that have marked
       * themselves as being expired and thus want to be removed from the game.
       */
      void reapDeadEntities();

      void loadLevel(const std::string& filename);

   private:
      State* mNextState;
      bool mIsQuitting;
      GameScene mGameScene;
      Camera mCamera;
      float mSpeed;
      Player mPlayer;



      //XXX hack for testing AIsystem

      typedef std::map<Entity::UID, lm::aiNode*> NodeMap;
      NodeMap mMap;

      lm::aiSystem AI;
      // the following was test related stuff

      testing* appTest;
      lm::aiNode* node1;
      lm::aiNode* node2;
      lm::command* node1sCommand;
      lm::command* node2sCommand;
      lm::command* aimCommand;
      lm::behavior* first;
      lm::behavior* second;
      lm::testing* myTestCommand;
      lm::testing* aimTestCommand;

      lm::reflex* node1Instinct;
      lm::reflex* node2Instinct;


      Scene* mScene;
      SceneViewer* mSceneViewer;

      /// The collision detection algorithm
      CollisionDetector* mCollDet;

      /**
       * Input data for the Player object.
       * @note    in local screen space, not actual player vel
       */
      gmtl::Vec3f mPlayerVel;

      /// This state's FPS
      float mFPS;
      float mFrameCount;
      float mFrameTime;

      /// The virtual cursor.
      Cursor mCursor;

      /// The heads up display used to give the user feedback about the world.
      HUD mHUD;

      // Actions
      InputAction* mActionUp;
      InputAction* mActionDown;
      InputAction* mActionRight;
      InputAction* mActionLeft;
      InputAction* mActionQuit;
      InputAction* mActionZoomIn;
      InputAction* mActionZoomOut;
      InputAction* mActionPitchUp;
      InputAction* mActionPitchDown;
      InputAction* mActionYawLeft;
      InputAction* mActionYawRight;

      // "Actions" that have not yet been converted over to use the InputBinder
      EdgeState mShoot, mCycleWeapon;
      std::vector<EdgeState> mGunSlots;

   };
}

#endif
