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
 * File:          $RCSfile: State.h,v $
 * Date modified: $Date: 2002-07-07 03:10:59 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#ifndef MW_STATE_H
#define MW_STATE_H

#include <assert.h>
#include <SDL.h>

namespace mw
{
   class Application;
   class State
   {
   public:
      State( Application* );
      virtual ~State();

      /**
       * Updates this state based on the amount of time, in seconds, that has
       * passed since the last frame.
       */
      virtual void update(float dt) = 0;

      virtual void draw() = 0;
      virtual void onKeyPress(SDLKey sym, bool down) = 0;
      virtual void onMousePress(Uint8 button, bool down, int x, int y) = 0;
      virtual void onMouseMove(int x, int y) = 0;
      Application& application() { assert( mApp != NULL ); return *mApp; }
      const Application& application() const { assert( mApp != NULL ); return *mApp; }
      
      void invokeTransition(State* state);

      /**
       * Returns the next State object, and makes the state forget about what
       * the next state is.
       */
      State* getNext();

      void quit();
      bool isQuitting();

   private:
      State* mNextState;
      bool mIsQuitting;
      Application* mApp;
   };
}

#endif
