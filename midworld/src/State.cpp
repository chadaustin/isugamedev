/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

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
