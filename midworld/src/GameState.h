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
 * Date modified: $Date: 2002-11-05 08:29:00 $
 * Version:       $Revision: 1.67 $
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
//#include <gmtl/LineSeg.h>
//#include <gmtl/Generate.h>
//#include <gmtl/QuatOps.h>

#include <SDL.h>
#include "Camera.h"
#include "Droid.h"
#include "CollisionDetector.h"
#include "Entity.h"
#include "GameScene.h"
#include "HUD.h"
#include "InputAction.h"
#include "Player.h"
#include "Scene.h"
#include "SceneViewer.h"
#include "State.h"
#include "Testing.h"
#include "Turret.h"
#include "PhysicsEngine.h"

namespace gmtl
{
   typedef Point<float, 2> Point2f;
}

namespace mw
{
   class Application;
   class testing;

   /**
    * The state in which the game is played.
    */
   class GameState : public State
   {
   public:
      GameState(Application* app);

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
       * Adds in a new navigation node to be used by the AI system for efficient
       * pathfinding.
       */
      void addNavNode(const gmtl::Vec3f& node);

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

      Turret* setupTurret(const std::string& name, const std::string& parent,
                          int maxChild, int level);
      Droid* setupDroid(const std::string& name, const std::string& parent,
                        int maxChild, int level);

   private:
      void initializeInput();
      
      void drawEntities();

      /// Draws the bounds around all the entities. For debugging purposes.
      void drawBounds();

      /// Called on input change
      void updateEdgeState(EdgeState& state, bool absoluteState);
      void updateEdgeState(InputAction& action, bool absoluteState);

      /// Called on update for each button
      void updateEdgeState(EdgeState& state);
      void updateEdgeState(InputAction& action);

      /**
       * Deletes and removes from the game all entities that have marked
       * themselves as being expired and thus want to be removed from the game.
       */
      void reapDeadEntities();

   private:
      State* mNextState;
      bool mIsQuitting;
      GameScene mGameScene;
      Camera mCamera;
      float mSpeed;
      Player mPlayer;
      std::vector<gmtl::Vec3f> navNodeIndex;


      //XXX hack for testing AIsystem

      typedef std::map<Entity::UID, lm::aiNode*> NodeMap;
      NodeMap mMap;

      // declare an instance of a loom aiSystem - the ai system for the game.
      lm::aiSystem AI;
      // the following was AI related stuff

      
      testing* appTest;
      std::vector<lm::aiNode*> mAInodes;
      lm::command* node1sCommand;
      lm::command* node2sCommand;
      lm::command* aimCommand;
      lm::command* shootCommand;
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

      /// The physics simulation engine
      PhysicsEngine* mPhysics;

      /**
       * Input data for the Player object.
       * @note    in local screen space, not actual player vel
       */
      gmtl::Vec3f mPlayerVel;

      /// This state's FPS
      float mFPS;
      float mFrameCount;
      float mFrameTime;

      /// The change in angle of the player's yaw for the next frame
      float mPlayerYawChange;

      /// Do we need to ignore the next mouse move because of the mouse warp?
      bool mIgnoreMouseMove;

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
