/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
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
 * File:          $RCSfile: State.cpp,v $
 * Date modified: $Date: 2003-02-03 02:54:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <assert.h>
#include "State.h"
#include "StateFactory.h"

namespace siren
{
   State::State()
      : mIsQuitting(false)
   {}

   State::~State()
   {}

   void
   State::onKeyPress(SDLKey sym, bool down)
   {}

   void
   State::onMousePress(Uint8 button, bool down, int x, int y)
   {}

   void
   State::onMouseMove(int x, int y)
   {}

   void
   State::invokeTransition(const std::string& name)
   {
      mNextState = StateFactory::getInstance().create(name);
   }

   StatePtr
   State::getNext()
   {
      StatePtr state = mNextState;
      mNextState.reset();
      return state;
   }

   void
   State::quit()
   {
      mIsQuitting = true;
   }

   bool
   State::isQuitting() const
   {
      return mIsQuitting;
   }
}
