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
 * Date modified: $Date: 2002-12-01 22:51:24 $
 * Version:       $Revision: 1.9 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <stdexcept>
#include <SDL_opengl.h>

#ifdef WIN32  // OpenSG needs Winsock  :(:(:(
#include <winsock.h>
#endif

#include <OpenSG/OSGNodePtr.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include "LoadState.h"
#include "StateFactory.h"
#include "ResourceManager.h"

namespace mw
{
   /**
    * The ResourceManager CachePolicy for osg::NodePtr objects.
    * XXX: HACK - This code is duplicated in OpenSGSceneViewer.cpp
    */
   template<>
   struct CachePolicy<osg::NodePtr>
   {
      static osg::NodePtr copy(osg::NodePtr cacheVal)
      {
         return osg::cloneTree(cacheVal);
      }

      static osg::NodePtr create(const std::string& name)
      {
         return osg::SceneFileHandler::the().read(name.c_str());
      }

      static void destroy(osg::NodePtr& val)
      {
         // do nothing ... osg::NodePtrs are ref counted
      }
   };

   LoadState::LoadState(Application* a)
      : State(a)
      , mModelsComplete(0)
      , mTexturesComplete(0)
   {
      mLoadImage = Texture::create("loading");
      mLoadingBar = Texture::create("loadingbar");

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

      mTextures.push_back("explosive_particle");
   }

   LoadState::~LoadState()
   {}

   void
   LoadState::update(float dt)
   {
      if (mModelsComplete < mModels.size())
      {
         ResourceManager& resmgr = ResourceManagerSingleton::instance();
         resmgr.preload<osg::NodePtr>(mModels[mModelsComplete]);
         ++mModelsComplete;
      }
      else if (mTexturesComplete < mTextures.size())
      {
         ResourceManager& resmgr = ResourceManagerSingleton::instance();
         resmgr.preload<Texture*>(mTextures[mTexturesComplete]);
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
      glDisable(GL_CULL_FACE);

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
      unsigned int bar_width = 456;
      unsigned int bar_height = 85;
      unsigned int total_complete = mModelsComplete + mTexturesComplete;
      unsigned int total_size = mModels.size() + mTextures.size();
      unsigned int value = (unsigned int)((float)total_complete / total_size * bar_width);

      mLoadingBar->drawRectangle(250, 660, 250 + value, 660 + bar_height);
   }
}
