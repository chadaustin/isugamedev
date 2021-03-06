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
 * File:          $RCSfile: Application.cpp,v $
 * Date modified: $Date: 2002-11-08 09:30:23 $
 * Version:       $Revision: 1.15 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <SDL_opengl.h>
#include "Application.h"
#include "GameManager.h"
#include "StateFactory.h"

namespace mw {

   Application::Application()
      : mWidth(0)
      , mHeight(0)
      , mState(0)
      , mNextState(0)
   {
      mState  = StateFactory::getInstance().create("Intro", this);
   }

   Application::~Application()
   {
      /// @todo  think about state management: who owns the memory?
      ///        are states allocated in a pool?  should states even
      ///        have state or should they be purely behavior?
      delete mState;
   }

   void
   Application::update(u64 elapsedTime)
   {
      // Check if we need to transition to the next state
      if (mNextState)
      {
         delete mState;
         mState = mNextState;
      }

      // Convert change in time to seconds
      float dt = static_cast<float>(elapsedTime) / 1000000.0f;

      // Make sure the jukebox gets updated
      GameManager::instance().getSoundManager()->getJukebox()->update();

      // Let the current state do its update
      mState->update(dt);

      // Store the transition to the next state
      mNextState = mState->getNext();
   }

   void
   Application::draw()
   {
      mState->draw();
   }

   void
   Application::resize(int width, int height)
   {
      mWidth  = width;
      mHeight = height;
   }

   void
   Application::onKeyPress(SDLKey sym, bool down)
   {
      mState->onKeyPress(sym, down);
   }

   void
   Application::onMousePress(Uint8 button, bool down, int x, int y)
   {
      mState->onMousePress(button, down, x, y);
   }

   void
   Application::onMouseMove(int x, int y)
   {
      mState->onMouseMove(x, y);
   }

   bool
   Application::shouldQuit()
   {
      return mState->isQuitting();
   }

}
