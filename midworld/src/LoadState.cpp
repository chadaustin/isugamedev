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
 * File:          $RCSfile: LoadState.cpp,v $
 * Date modified: $Date: 2002-10-31 07:22:17 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <stdexcept>
#include <SDL_opengl.h>
#include "LoadState.h"
#include "StateFactory.h"
#include "GameManager.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<LoadState> creator("Load");
   }

   LoadState::LoadState(Application* a)
      : State(a)
      , mModelsComplete(0)
      , mTexturesComplete(0)
   {
      mLoadImage = new Texture("images/loading.jpeg");

      mModels.push_back("ammo_crate");
      mModels.push_back("barrel");
      mModels.push_back("barrel_tipped");
      mModels.push_back("bullet");
      mModels.push_back("casing");
      mModels.push_back("player");
      mModels.push_back("security_droid");
      mModels.push_back("tent");
      mModels.push_back("turret");
      mModels.push_back("wall_straight");
      mModels.push_back("wall_corner");

      mTextures.push_back("images/explosive_particle.png");
   }

   LoadState::~LoadState()
   {
      delete mLoadImage;
   }

   void
   LoadState::update(float dt)
   {
      if (mModelsComplete < mModels.size())
      {
         ResourceManager* resmgr = GameManager::instance().getResourceManager();
         ModelManager* mdlmgr = GameManager::instance().getModelManager();

         mdlmgr->preload(resmgr->get(mModels[mModelsComplete]));
         ++mModelsComplete;
      }
      else if (mTexturesComplete < mTextures.size())
      {
         TextureManager* texmgr = GameManager::instance().getTextureManager();
         texmgr->preload(mTextures[mTexturesComplete]);
         ++mTexturesComplete;
      }
      else
      {
         invokeTransition("Game");
      }
   }

   void
   LoadState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);

      glClear(GL_COLOR_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, application().getWidth(), application().getHeight(), 0);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      // Background image
      glColor3f(1, 1, 1);
      mLoadImage->drawRectangle(
         0, 0, application().getWidth(), application().getHeight());

      // Draw the status bar
      unsigned int half_width = application().getWidth() / 2;
      unsigned int bar_size = 200;
      unsigned int total_complete = mModelsComplete + mTexturesComplete;
      unsigned int total_size = mModels.size() + mTextures.size();
      unsigned int value = (unsigned int)((float)total_complete / total_size * 200.0f);

      glPushMatrix();
      {
         glTranslatef(half_width - bar_size/2, application().getHeight() - 50, 0);
         glBegin(GL_QUADS);
            glColor3f(1,0,0);
            glVertex2f(0,     0);
            glVertex2f(0,     20);
            glVertex2f(value, 20);
            glVertex2f(value, 0);

            glColor3f(0,0,0);
            glVertex2f(value, 0);
            glVertex2f(value, 20);
            glVertex2f(bar_size,   20);
            glVertex2f(bar_size,   0);
         glEnd();
      }
      glPopMatrix();
   }
}
