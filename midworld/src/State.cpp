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
 * File:          $RCSfile: State.cpp,v $
 * Date modified: $Date: 2002-07-07 02:21:11 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */

#include "State.h"


namespace mw
{
   State::State()
   {
      mNextState = 0;
      mIsQuitting = false;
   }

   State::~State()
   {
      delete mNextState;
   }

   void
   State::invokeTransition(State* state)
   {
      delete mNextState;
      mNextState = state;
   }

   State*
   State::getNext()
   {
      State* state = mNextState;
      mNextState = 0;
      return state;
   }

   void
   State::quit()
   {
      mIsQuitting = true;
   }

   bool
   State::isQuitting()
   {
      return mIsQuitting;
   }
}
