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
 * Date modified: $Date: 2002-12-21 19:25:49 $
 * Version:       $Revision: 1.78 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_GAME_STATE_H
#define MW_GAME_STATE_H

#include <map>
#include <vector>

#include "cal3d/cal3d.h"

#include <loom/aiSystem.h>
#include <loom/reflex.h>
#include <loom/behavior.h>
#include <loom/unit.h>
#include <loom/command.h>

#include <gmtl/Point.h>

#include <SDL.h>
#include "Camera.h"
#include "Droid.h"
#include "CollisionDetector.h"
#include "Entity.h"
#include "FPSCounter.h"
#include "GameScene.h"
#include "HUD.h"
#include "InputAction.h"
#include "InputManager.h"
#include "NavNodeTree.h"
#include "Player.h"
#include "Scene.h"
#include "SceneViewer.h"
#include "State.h"
#include "Testing.h"
#include "Turret.h"
#include "PhysicsEngine.h"
#include "SnowSystem.h"
#include "PerformanceMonitor.h"


namespace gmtl
{
   typedef Point<float, 2> Point2f;
}

namespace mw
{
   class Application;
   class testing;
   class NavNodeTree;
   class Node;
   
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
      void addNavNode(Node* node);

      /** 
       * adds in a new link between navigation nodes to be used by loom for
       * efficient pathfinding.
       */
      void addNavNodeLink(std::string n1, std::string n2);
      
      NavNodeTree* getNavNodeTree(){ return droidNavTree; }
      
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
      

      void cleanUpCal3d();
      
      Turret* setupTurret(const std::string& name, const std::string& parent,
                          int maxChild, int level);
      Droid* setupDroid(const std::string& name, const std::string& parent,
                        int maxChild, int level, NavNodeTree& tree);
      

      
   private:
      void initializeInput();
      
      void drawEntities();

      /// Draws the bounds around all the entities. For debugging purposes.
      void drawBounds();

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

      // navigation tree for the droids
      NavNodeTree* droidNavTree;

      //XXX hack for testing AIsystem

      typedef std::map<Entity*, lm::aiNode*> NodeMap;
      NodeMap mMap;

      // declare an instance of a loom aiSystem - the ai system for the game.
      lm::aiSystem AI;
      // the following was AI related stuff

      
      testing* appTest;
      std::vector<lm::aiNode*> mAInodes;
      
      // this is the test case to see if the player is in range
      lm::testing* aimTestCommand;
      // this is the shoot pivot and shoot command
      lm::command* aimCommand;
      // this is the behavior that we stor aimCommand into 
      lm::behavior* first;
      // this is the turrets only reflex
      lm::reflex* node1Instinct;
      
      // this is the droids reaction if myTestCommand comes true
      lm::command* shootCommand;
      // the behavior that shootCommand gets stored into 
      lm::behavior* second;
      // for droids this test to see if the player is out in front of the droid
      lm::testing* myTestCommand;
      // reflex for the droid
      lm::reflex* node2Instinct;

      // droidFuked is the reflex associated with checking if a droids
      // fuckedflag is currently set
      lm::reflex* droidFuked;
      // fukedTest returns true if the droids fukedflag is set
      lm::testing* fukedTest;
      // fuckedCommand is the reaction for fukedTest
      lm::command* fuckedCommand;
      // fuckedBehavior is the behaivor that stores the fuckedCommand
      lm::behavior* fuckedBehavior;

      // atGoalNode is the reflex associated with checking if a droid is at the
      // goal node
      lm::reflex* atGoalNode;
      // goalTest returns true if the droid is at the goal node
      lm::testing* goalTest;
      // goalCommand is the reaction for the goalTest
      lm::command* goalCommand;
      // goalBehavior is the behavior that stores teh goalCommand
      lm::behavior* goalBehavior;

      // defualtDroidAction is the reflex that is always called and handle moving
      // the droid around
      lm::reflex* defaultDroidAction;
      // moveCommand is the command that moves the droid every frame toward
      // whatever is most important
      lm::command* moveCommand;
      // moveBehavior stores moveCommand
      lm::behavior* moveBehavior;
      // moveTest returns true always
      lm::testing* moveTest;

      

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

      FPSCounter mFPSCounter;
      PerformanceMonitor mPM;

      /// The change in angle of the player's yaw for the next frame
      float mPlayerYawChange;

      /// Do we need to ignore the next mouse move because of the mouse warp?
      bool mIgnoreMouseMove;

      /// The heads up display used to give the user feedback about the world.
      HUD mHUD;


      /// Animation stuff
      CalCoreModel mPlayerCoreModel;
      int startWalkingAnimationID;
      int walkingAnimationID;
      int meshID;
      int pantsMaterialID;
      int hatMaterialID;
      int coatMaterialID;
      bool drawAni;
      
      CalModel myModel;
      CalRenderer *pCalRenderer;
      

      void drawAnimation();
      
      

      /// This is the skydome texture
      Texture* mSkydomeTex;

      /// The system that controls the snow in the level
      SnowSystem mSnowSystem;

      // Actions
      InputManager mInputManager;
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
      InputAction* mActionShoot;
      InputAction* mActionCycleWeapon;
   };
}

#endif
