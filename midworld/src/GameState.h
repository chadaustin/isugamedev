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
      GameState() : mSpeed( 150 )
      {
      }
      
      virtual ~GameState()
      {
      }

      virtual void update( u64 elapsedTime )
      {
         mStopWatch.pulse();
         mCamera.setPlayerPos( mPlayer.position() );
         if (mAccelerate == true)
         {
            mPlayer.setVelocity( gmtl::Vec3f( 0,0, -mSpeed * mStopWatch.timeDelta() ) );
         }
         else
         {
            mPlayer.setVelocity( gmtl::Vec3f( 0, 0, 0 ) );
         }
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
             mAccelerate = down;
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
      }

   private:
      State* mNextState;
      bool mIsQuitting;
      GameScene mScene;
      Camera mCamera;
      StopWatch mStopWatch;
      float mSpeed;
      Player mPlayer;
      
      // actions :*)
      bool mAccelerate;
   };

}


#endif
