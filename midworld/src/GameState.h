/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_GAMESTATE_H
#define MW_GAMESTATE_H

#include <vector>

#include <SDL.h>
#include <gltext.h>
#include "State.h"
#include "GameScene.h"
#include "Camera.h"
#include "Player.h"
#include "RigidBody.h"

namespace mw
{
   class GameState : public State
   {
   public:
      GameState();
      ~GameState();

      enum EdgeState
      {
         DOWN, UP, EDGE_DOWN, EDGE_UP
      };

      void update(u64 elapsedTime);

      void draw();

      void onKeyPress(SDLKey sym, bool down);

      void onMousePress(Uint8 button, bool down, int x, int y);

      void onMouseMove(int x, int y);

      void add( RigidBody* );

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

      // actions :*)
      EdgeState mAccelerate;
      EdgeState mReverse;
      EdgeState mStrafeRight, mStrafeLeft;
      EdgeState mShoot, mCycleWeapon;
      
      // input data for the Player object.
      // note: in local screen space, not actual player vel
      gmtl::Vec3f mPlayerVel;

      gltext::Font* mFont;
      gltext::FontRenderer* mFontRenderer;

      // This state's FPS
      float mFPS;
   };
}

#endif
