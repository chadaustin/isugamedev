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
 * Date modified: $Date: 2003-02-25 06:39:39 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** barfight-cpr-end */
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
      : mDrunkAmount(0.0f)
      , mIgnoreMouseMove(true)
      , mFPS(0.0f)
      , mNumFrames(0)
      , mFrameTime(0.0f)
   {
      mPlayer = siren::Avatar::create("John");
//      mAvatar->setDrawMode(siren::Avatar::DrawSkeleton);
//      mAvatar->triggerAnimationCycle("RUN");
//      mAvatar->triggerAnimationCycle("DANCE");
      mPlayer->setWCS(gmtl::EulerAngleXYZf(gmtl::Math::deg2Rad(-90.0f),0,0));
      mPlayer->setRot(gmtl::makeRot<gmtl::Quatf>(gmtl::AxisAnglef(180.0f, 0,1,0)));

      for (int i=0; i<4; ++i)
      {
         siren::Avatar* av = siren::Avatar::create("John");
         av->setWCS(gmtl::EulerAngleXYZf(gmtl::Math::deg2Rad(-90.0f),0,0));
         av->setPos(gmtl::Point3f(4.0f*i, 0, -10));
         mNPCs.push_back(av);
      }

      mAnim = 0;
      mAnims.push_back("WALK");
      mAnims.push_back("RUN");
      mAnims.push_back("DANCE");
      mAnims.push_back("IDLE");
      mAnims.push_back("TYPE");
      mAnims.push_back("SIT");
      mAnims.push_back("WORK1");
      mAnims.push_back("WORK2");


      // Create the texture to hold the motion blur
      mBlurTexture = new siren::Texture(512, 512, 3, GL_RGB);

      // init the GL state
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_TEXTURE_2D);

      glClearColor(0, 0, 0, 1);
   }

   GameState::~GameState()
   {
      std::cout<<"Killing off GameState"<<std::endl;
      delete mBlurTexture;
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
      mCamera.draw();
      // Redraw the current blur texture
      glPushAttrib(GL_VIEWPORT_BIT);
         // Change the viewport to match the size of the texture
         glViewport(0, 0, mBlurTexture->getTexWidth(), mBlurTexture->getTexHeight());
         drawMotionBlur();
         drawScene();

         // Copy the contents of the frame buffer into our blur texture
         mBlurTexture->bind();
         glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0,
                          mBlurTexture->getTexWidth(), mBlurTexture->getTexHeight(),
                          0);
         mBlurTexture->unbind();

         // Clear the frame buffer again
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glPopAttrib();

      // Blend in the motion blur with the background color
      drawMotionBlur();

      // Draw the scene on top of motion blur
      drawScene();

      // Check to see if we caused problems with our OpenGL code
      if (glGetError() != GL_NO_ERROR)
      {
         std::cerr << "I fucked up my GL State." << std::endl;
      }
   }

   void
   GameState::update(float dt)
   {
      // Update the avatar
      mPlayer->update(dt);
      
      // Update Camera
      mCamera.setTarget(mPlayer->getPos(), mPlayer->getRotQuat());
      mCamera.update(dt);
      
      for (size_t i=0; i<mNPCs.size(); ++i)
      {
         mNPCs[i]->update(dt);
      }

      // Calculate the FPS
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
         else if (sym == SDLK_SPACE)
         {
            mPlayer->stopAnimation(mAnims[mAnim]);
            mAnim = (mAnim + 1) % mAnims.size();
            mPlayer->triggerAnimationCycle(mAnims[mAnim]);
         }
         else if (sym == SDLK_LCTRL)
         {
            mDrunkAmount += 0.05f;
            if (mDrunkAmount > 1.0f)
            {
               mDrunkAmount = 1.0f;
            }
         }
         else if (sym == SDLK_LALT)
         {
            mDrunkAmount -= 0.05f;
            if (mDrunkAmount < 0.0f)
            {
               mDrunkAmount = 0.0f;
            }
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

   void
   GameState::drawMotionBlur() const
   {
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // Turn off depth testing so that we blend over the screen
         glDisable(GL_DEPTH_TEST);

         // Enable blending
         glBlendFunc(GL_SRC_ALPHA, GL_ONE);
         glEnable(GL_BLEND);

         // Decrease alpha value of the blend by 10% so that it will fade
//         float decay = mDrunkAmount;
         float decay = 0.95f;
         glColor4f(1, 1, 1, decay);

         // Switch to an orthograhic view
         glMatrixMode(GL_PROJECTION);
         glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, getWidth(), getHeight(), 0);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            // Blend the texture into the screen
            mBlurTexture->bind();
            glBegin(GL_QUADS);
               glTexCoord2f(0, 1); glVertex2f(0, 0);
               glTexCoord2f(0, 0); glVertex2f(0, getHeight());
               glTexCoord2f(1, 0); glVertex2f(getWidth(), getHeight());
               glTexCoord2f(1, 1); glVertex2f(getWidth(), 0);
            glEnd();
            mBlurTexture->unbind();

            glPopMatrix();
            glMatrixMode(GL_PROJECTION);

         // Switch back to the old projection
         glPopMatrix();
         glMatrixMode(GL_MODELVIEW);
      glPopAttrib();
   }

   void
   GameState::drawScene() const
   {
      glPushMatrix();
         // Draw the avatar
         glTranslatef(0, -5.0f, -5.0f);
         mPlayer->render();

         for (size_t i=0; i<mNPCs.size(); ++i)
         {
            mNPCs[i]->render();
         }
      glPopMatrix();
   }
}
