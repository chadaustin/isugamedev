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
 * File:          $RCSfile: IntroState.cpp,v $
 * Date modified: $Date: 2003-06-16 08:14:56 $
 * Version:       $Revision: 1.27 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <algorithm>
#include <memory>
#include <iostream>
#include "IntroState.h"
#include "GameManager.h"
#include "Application.h"
#include "StateFactory.h"

namespace mw
{
   IntroState::IntroState( Application* a )
      : State( a )
      , mAutoNextTime(8)
      , mElapsedTime(0)
      , mLeavingState(false)
   {
      mIntroImage = Texture::create("intro");
      // Start playing the theme song.
      Jukebox* jukebox = GameManager::instance().getSoundManager()->getJukebox();
      jukebox->clear();
      jukebox->addTrack("music/theme.ogg");
      jukebox->play();
   }

   IntroState::~IntroState()
   {}

   void
   IntroState::update(float dt)
   {
      mElapsedTime += dt;

      // Check if we need to start the auto transition to the next state
      if (mElapsedTime > mAutoNextTime)
      {
         startTransition();
      }
      
      if (mLeavingState && mElapsedTime > 1)
      {
         invokeTransition("Menu");
      }
      ::SDL_WarpMouse( this->application().getWidth() / 2, this->application().getHeight() / 2 );
   }

   void
   IntroState::draw()
   {
      /// @todo  think about GL states

      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);

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
      mIntroImage->drawRectangle(0, 0, 1, 1);
   }

   void
   IntroState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         startTransition();
      }
   }

   void
   IntroState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      if (down)
      {
         startTransition();
      }
   }

   void
   IntroState::startTransition()
   {
      if (!mLeavingState)
      {
         mLeavingState = true;
         mElapsedTime = std::max(0.0f, 1.0f - mElapsedTime);
      }
   }

}
