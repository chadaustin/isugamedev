/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
#include <sstream>
#include "GameState.h"
#include "IntroState.h"
#include "MenuState.h"
#include "Pistol.h"
#include "SpreadGun.h"
#include "Shotgun.h"

namespace mw
{
   GameState::GameState()
      : mSpeed(10)
      , mAccelerate(UP)
      , mReverse(UP)
      , mStrafeRight(UP)
      , mStrafeLeft(UP)
      , mShoot(UP)
      , mCycleWeapon(UP)
      , mFPS(0)
      , mFrameCount(0)
      , mFrameTime(0)
   {
      mPlayer.addWeapon( new Pistol );
      mPlayer.addWeapon( new SpreadGun );
      mPlayer.addWeapon( new Shotgun );
      for (int i = 0; i < 10; i++)
      {
         mEnemies.push_back(new Enemy());
         add(mEnemies[i]);
      }
      
      mFont = 0;
      mFontRenderer = 0;
      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (mFont)
      {
         std::cout<<"Font font"<<std::endl;
         mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
         if (mFontRenderer)
         {
            std::cout<<"Created renderer"<<std::endl;
            mFontRenderer->setFont(mFont);
         }
      }
   }

   GameState::~GameState()
   {
   }

   void
   GameState::update(float dt)
   {
      mCamera.setPlayerPos(mPlayer.getPos());

      const gmtl::Vec3f accel(   gmtl::Vec3f(0, 0, -mSpeed)      );
      const gmtl::Vec3f reverse( gmtl::Vec3f(0, 0,  mSpeed*0.7f) );
      const gmtl::Vec3f sleft(   gmtl::Vec3f(-mSpeed*0.9f, 0, 0) );
      const gmtl::Vec3f sright(  gmtl::Vec3f( mSpeed*0.9f, 0, 0) );
      
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
      mPlayer.setVel( mPlayer.getRot() * mPlayerVel );
      
      // Shoot
      if (mShoot == EDGE_DOWN)
      {
         mPlayer.weapon().trigger( true );
         //std::cout<<"Trigger Down"<<std::endl;
      }
      else if (mShoot == EDGE_UP)
      {
         mPlayer.weapon().trigger( false );
         //std::cout<<"Trigger Up"<<std::endl;
      }
      
      if (mCycleWeapon == EDGE_DOWN)
      {
         mPlayer.nextWeapon();
      }      

      // update edge states...
      updateEdgeState(mAccelerate);
      updateEdgeState(mReverse);
      updateEdgeState(mStrafeRight);
      updateEdgeState(mStrafeLeft);
      updateEdgeState(mShoot);
      updateEdgeState(mCycleWeapon);

      

      // Iterate over all the rigid bodies and update them
      for (RigidBodyList::iterator itr = mBodies.begin(); itr != mBodies.end(); ++itr)
      {
         (*itr)->update(dt);
      }

      mCamera.update( dt );
      mPlayer.update( *this, dt);

      ++mFrameCount;
      mFrameTime += dt;
      if (mFrameTime > 0.5f)
      {
         mFPS = mFrameCount / mFrameTime;
         mFrameCount = 0;
         mFrameTime = 0;
      }
   }

   void GameState::add( RigidBody* b )
   {
      mBodies.push_back( b );
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
         mPlayer.draw();
         mScene.draw();

         // Draw all the bodies in the world
         for (RigidBodyList::iterator itr = mBodies.begin(); itr != mBodies.end(); ++itr)
         {
            (*itr)->draw();
         }
      glPopMatrix();

      // Draw the HUD
      if (mFontRenderer)
      {
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
         glLoadIdentity();
         glOrtho(0, 640, 480, 0, 1, -1);

         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glLoadIdentity();

         glPushMatrix();
            glTranslatef(20, 20.0f+mFont->getAscent(), 0);
            glColor4f(1,0,0,0.8f);
            mFontRenderer->render("Midworld");
         glPopMatrix();

         glPushMatrix();
            glTranslatef(550, 480 - mFont->getAscent() - mFont->getDescent(), 0);
            glColor4f(1,0,0,1);
            {
               std::stringstream str;
               str << mPlayer.weapon().getAmmoInClip();
               mFontRenderer->render(str.str().c_str());
            }
            glTranslatef(40, 0, 0);
            {
               std::stringstream str;
               str << mPlayer.weapon().getAmmoInBag();
               mFontRenderer->render(str.str().c_str());
            }
         glPopMatrix();

         // FPS
         glPushMatrix();
         glTranslatef(550, 20.0f+mFont->getAscent(), 0);
         glColor4f(1,1,1,1);
         {
            std::stringstream str;
            str << (int)mFPS;
            mFontRenderer->render(str.str().c_str());
         }
         glPopMatrix();

         glPushMatrix();
         glTranslatef(20, 480.0f - mFont->getAscent() - mFont->getDescent(), 0);
         glColor4f(1,0,0,1);
         mFontRenderer->render(mPlayer.weapon().getName().c_str());
         glPopMatrix();

         glPopMatrix();
         glPopMatrix();
      }
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
            invokeTransition(new MenuState());
         }
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
      float screen_size_x = 640;
      float screen_size_y = 480;
      gmtl::Vec3f mid(screen_size_x / 2, screen_size_y / 2, 0);
      gmtl::Vec3f pos((float)x, (float)y, 0);
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

   void
   GameState::updateEdgeState(EdgeState& state, bool absoluteState)
   {
      switch (state)
      {
         case DOWN: if (!absoluteState) state = EDGE_UP; break;
         case UP: if (absoluteState) state = EDGE_DOWN; break;
         case EDGE_DOWN: if (absoluteState) state = DOWN; break;
         case EDGE_UP: if (!absoluteState) state = UP; break;
      }
   }

   void
   GameState::updateEdgeState(EdgeState& state)
   {
      switch (state)
      {
         case EDGE_DOWN: state = DOWN; break;
         case EDGE_UP: state = UP; break;
         default: break;
      }
   }
}
