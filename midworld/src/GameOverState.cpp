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
 * File:          $RCSfile: GameOverState.cpp,v $
 * Date modified: $Date: 2002-11-02 23:11:11 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <algorithm>
#include <memory>
#include <iostream>
#include "Application.h"
#include "GameManager.h"
#include "GameOverState.h"
#include "StateFactory.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<GameOverState> creator("GameOver");
   }

   GameOverState::GameOverState(Application* a)
      : State(a)
      , mElapsedTime(0)
      , mLeavingState(false)
   {
      mImage = new Texture("images/gameover.jpeg");
      // Start playing the theme song.
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->clear();
      jukebox->addTrack("music/theme.ogg");
      jukebox->play();
   }

   GameOverState::~GameOverState()
   {
      delete mImage;
   }

   void
   GameOverState::update(float dt)
   {
      mElapsedTime += dt;

      if (mLeavingState && mElapsedTime > 1)
      {
         invokeTransition("Menu");
      }
      ::SDL_WarpMouse(
         application().getWidth() / 2,
         application().getHeight() / 2);
   }

   void
   GameOverState::draw()
   {
      /// @todo  think about GL states

      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, 1, 1, 0);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
            
      float fade = (mLeavingState ?
                    1 - mElapsedTime :
                    std::min(mElapsedTime, 1.0f));
      glColor3f(fade, fade, fade);
      mImage->drawRectangle(0, 0, 1, 1);
   }

   void
   GameOverState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         startTransition();
      }
   }

   void
   GameOverState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      if (down)
      {
         startTransition();
      }
   }

   void
   GameOverState::startTransition()
   {
      if (!mLeavingState)
      {
         mLeavingState = true;
         mElapsedTime = std::max(0.0f, 1.0f - mElapsedTime);
      }
   }
}
