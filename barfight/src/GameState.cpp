/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* barfight-cpr beg
 *
 * barfight - a slapstick drag-out brawl at the local pub
 * barfight is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * Date modified: $Date: 2003-02-21 08:48:46 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
#include <memory>
#include <stdexcept>
#include <vector>
#include <gmtl/EulerAngle.h>
#include <gmtl/Math.h>
#include <siren/siren.h>

#ifdef _MSC_VER
#  include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include "GameState.h"


namespace bar
{
   GameState::GameState()
      : mIgnoreMouseMove(true)
      , mFPS(0.0f)
      , mNumFrames(0)
      , mFrameTime(0.0f)
   {
      mAvatar = siren::Avatar::create("John");
//      mAvatar->setDrawMode(siren::Avatar::DrawSkeleton);
//      mAvatar->triggerAnimationCycle("RUN");
//      mAvatar->triggerAnimationCycle("DANCE");
      mAvatar->setWCS(gmtl::EulerAngleXYZf(gmtl::Math::deg2Rad(-90.0f),0,0));

      mAnim = 0;
      mAnims.push_back("WALK");
      mAnims.push_back("RUN");
      mAnims.push_back("DANCE");
      mAnims.push_back("IDLE");
      mAnims.push_back("TYPE");
      mAnims.push_back("SIT");
      mAnims.push_back("WORK1");
      mAnims.push_back("WORK2");

      // init the GL state
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_TEXTURE_2D);

      glClearColor(0, 0, 0, 1);
   }

   GameState::~GameState()
   {
      std::cout<<"Killing off GameState"<<std::endl;
   }

   void
   GameState::draw() const
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(80.0f, (float)getWidth()/(float)getHeight(), 0.01f, 500.0f);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glPushMatrix();
         // Draw the avatar
         glTranslatef(0, -5.0f, -5.0f);
         mAvatar->render();
      glPopMatrix();

      // Check if we screwed up our GL code somewhere
      if (glGetError() != GL_NO_ERROR)
      {
         std::cerr << "I fucked up my GL State." << std::endl;
      }
   }

   void
   GameState::update(float dt)
   {
      mAvatar->update(dt);

      ++mNumFrames;
      mFrameTime += dt;
      if (mFrameTime > 0.5f)
      {
         mFPS = (float)mNumFrames / mFrameTime;
         mFrameTime = 0.0f;
         mNumFrames = 0;
         std::cout << "FPS: " << mFPS << std::endl;
      }
   }

   void
   GameState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         if (sym == SDLK_ESCAPE || sym == SDLK_q)
         {
            quit();
         }
         if (sym == SDLK_SPACE)
         {
            mAvatar->stopAnimation(mAnims[mAnim]);
            mAnim = (mAnim + 1) % mAnims.size();
            mAvatar->triggerAnimationCycle(mAnims[mAnim]);
         }
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

      gmtl::Point2i center(getWidth() / 2, getHeight() / 2);
      gmtl::Point2i diff(x - center[0], y - center[1]);

//      mRotX += diff[1];
//      mRotY += diff[0];

      SDL_WarpMouse(center[0], center[1]);
      mIgnoreMouseMove = true;
   }
}
