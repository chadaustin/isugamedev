/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_GAMESTATE_H
#define MW_GAMESTATE_H

#include <SDL/SDL.h>
#include "State.h"
#include <StopWatch.h>
#include "GameScene.h"
#include "Camera.h"
#include "Player.h"
#include "IntroState.h"

namespace mw
{

   class GameState : public State
   {
   public:
      GameState() : mSpeed( 3 ), mAccelerate( UP ), mReverse( UP ), mStrafeRight( UP ), mStrafeLeft( UP )
      {
      }
      
      virtual ~GameState()
      {
      }

      enum EdgeState
      {
         DOWN, UP, EDGE_DOWN, EDGE_UP
      };
         
      virtual void update( u64 elapsedTime )
      {
         double time_delta = ((double)elapsedTime) / 1000000.0;
         mCamera.setPlayerPos( mPlayer.position() );
         
         // process input events:
         if (mAccelerate == EDGE_DOWN)
            mPlayer.setVelocity( mPlayer.velocity() + gmtl::Vec3f( 0,0, -mSpeed ) );
         else if (mAccelerate == EDGE_UP)
            mPlayer.setVelocity( mPlayer.velocity() - gmtl::Vec3f( 0,0, -mSpeed ) );
         
         if (mReverse == EDGE_DOWN)
            mPlayer.setVelocity( mPlayer.velocity() + gmtl::Vec3f( 0,0, mSpeed*0.7f ) );
         else if (mReverse == EDGE_UP)
            mPlayer.setVelocity( mPlayer.velocity() - gmtl::Vec3f( 0,0, mSpeed*0.7f ) );
         
         if (mStrafeLeft == EDGE_DOWN)
            mPlayer.setVelocity( mPlayer.velocity() + gmtl::Vec3f( -mSpeed*0.9f,0,0 ) );
         else if (mStrafeLeft == EDGE_UP)
            mPlayer.setVelocity( mPlayer.velocity() - gmtl::Vec3f( -mSpeed*0.9f,0,0 ) );
         
         if (mStrafeRight == EDGE_DOWN)
            mPlayer.setVelocity( mPlayer.velocity() + gmtl::Vec3f( mSpeed*0.9f,0,0 ) );
         else if (mStrafeRight == EDGE_UP)
            mPlayer.setVelocity( mPlayer.velocity() - gmtl::Vec3f( mSpeed*0.9f,0,0 ) );
         
         // update edge states...
         this->updateEdgeState( mAccelerate );
         this->updateEdgeState( mReverse );
         this->updateEdgeState( mStrafeRight );
         this->updateEdgeState( mStrafeLeft );
         
         
         mCamera.update( time_delta );
         mPlayer.update( time_delta );
      }

      virtual void draw()
      {
         glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
         glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
         glEnable( GL_DEPTH_TEST );
         glEnable( GL_BLEND );
         glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

         glMatrixMode( GL_PROJECTION );
         glLoadIdentity();         

         /// @todo get rid of this...     maybe the clearing buffer too...       
         gluPerspective( 80.0f, 4.0f/3.0f, 0.01f, 10000.0f );

         // initialize your matrix stack used for transforming your models
         glMatrixMode( GL_MODELVIEW );
         glLoadIdentity();      
   
         glPushMatrix();
            mCamera.draw();
            mPlayer.draw();
            mScene.draw();
         glPopMatrix();
      }

      virtual void onKeyPress( SDLKey sym, bool down )
      {
         // todo replace this with a keymapper.
         // map keys to events... yay.
         switch (sym)
         {
           case SDLK_w: case SDLK_UP:
             this->updateEdgeState( mAccelerate, down );
             break;
           case SDLK_s: case SDLK_DOWN:
             this->updateEdgeState( mReverse, down );
             break;
           case SDLK_a: case SDLK_LEFT:
             this->updateEdgeState( mStrafeLeft, down );
             break;
           case SDLK_d: case SDLK_RIGHT:
             this->updateEdgeState( mStrafeRight, down );
             break;
           case SDLK_ESCAPE: case SDLK_q:
             if (down) this->invokeTransition( new MenuState ); 
             break;
         }
      }
            
      virtual void onMousePress( Uint8 button, bool down, int x, int y )
      {
         
         
      }
      
      virtual void onMouseMove( int x, int y )
      {
         float screen_size_x = 640;
         float screen_size_y = 480;
         gmtl::Vec3f mid( screen_size_x / 2, screen_size_y / 2, 0 );
         gmtl::Vec3f pos( x, y, 0 );
         gmtl::Vec3f dir( pos - mid );
         gmtl::normalize( dir );
         
         float rad = gmtl::Math::aCos( gmtl::dot( dir, gmtl::Vec3f( 1,0,0 ) ) );
         gmtl::Vec3f side = gmtl::cross( dir, gmtl::Vec3f( 1,0,0 ) );
         
         // move so it points in mouse dir...
         rad += gmtl::Math::deg2Rad( 90.0f );
         
         // map the dot (angle) and cross (side) to the player
         if (side[2] >= 0.0f)
         {
            mPlayer.setRot( rad + gmtl::Math::deg2Rad( 180.0f ) );
         }
         else
         {
            mPlayer.setRot( -rad );
         }
      }

   private:
      // called on input change
      void updateEdgeState( EdgeState& state, bool absoluteState )
      {
         switch (state)
         {
            case DOWN: if (!absoluteState) state = EDGE_UP; break;
            case UP: if (absoluteState) state = EDGE_DOWN; break;
            case EDGE_DOWN: if (absoluteState) state = DOWN; break;
            case EDGE_UP: if (!absoluteState) state = UP; break;
         }         
      }
      // called on update for each button
      void updateEdgeState( EdgeState& state )
      {
         switch (state)
         {
            case EDGE_DOWN: state = DOWN; break;
            case EDGE_UP: state = UP; break;
            default: break;
         }         
      }
         
      State* mNextState;
      bool mIsQuitting;
      GameScene mScene;
      Camera mCamera;
      StopWatch mStopWatch;
      float mSpeed;
      Player mPlayer;
      
      // actions :*)
      EdgeState mAccelerate;
      EdgeState mReverse;
      EdgeState mStrafeRight, mStrafeLeft;
   };

}


#endif
