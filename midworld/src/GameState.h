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
 * Date modified: $Date: 2002-07-07 06:21:47 $
 * Version:       $Revision: 1.26 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef MW_GAMESTATE_H
#define MW_GAMESTATE_H

#include <vector>

#include <SDL.h>
#include <gltext.h>
#include "State.h"
#include "GameScene.h"
#include "Camera.h"
#include "Player.h"
#include "BaseBullet.h"
#include "Enemy.h"
#include "RigidBody.h"
#include "GrimReaper.h"
#include "Cursor.h"

namespace mw
{
   class Application;
   class GameState : public State
   {
   public:
      GameState( Application* a );
      ~GameState();

      enum EdgeState
      {
         DOWN, UP, EDGE_DOWN, EDGE_UP
      };

      void update(float dt);

      void draw();

      void onKeyPress(SDLKey sym, bool down);

      void onMousePress(Uint8 button, bool down, int x, int y);

      void onMouseMove(int x, int y);
      /**
       * Adds a RigidBody into the world
       * @param b the body to add into the world
       */
      void add( RigidBody* b);
      /**
       * Adds a bullet into the world
       * @param bullet the bullet to add into the world.
       */
      void add( BaseBullet* bullet);
      /**
       * Adds an enemy into the world
       * @param enemy the enemy to add into the world.
       */
      void add( Enemy* enemy);
   private:
      // called on input change
      void updateEdgeState(EdgeState& state, bool absoluteState);

      // called on update for each button
      void updateEdgeState(EdgeState& state);

   private:
      State* mNextState;
      bool mIsQuitting;
      GameScene mScene;
      Camera mCamera;
      float mSpeed;
      Player mPlayer;

      typedef std::vector<RigidBody*> RigidBodyList;
      RigidBodyList mBodies;
      std::vector<Enemy*> mEnemies;
      std::vector<BaseBullet*> mBullets;
      GrimReaper *mReaper;
      // actions :*)
      EdgeState mAccelerate;
      EdgeState mReverse;
      EdgeState mStrafeRight, mStrafeLeft;
      EdgeState mShoot, mCycleWeapon;
      std::vector<EdgeState> mGunSlots; 
      // input data for the Player object.
      // note: in local screen space, not actual player vel
      gmtl::Vec3f mPlayerVel;

      gltext::Font* mFont;
      gltext::FontRenderer* mFontRenderer;

      // This state's FPS
      float mFPS;
      float mFrameCount;
      float mFrameTime;
      
      Cursor mCursor;
   };
}

#endif
