/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputAction.h"

namespace mw
{
   unsigned long InputAction::getID()
   {
      return mID;
   }

   EdgeState InputAction::getState()
   {
      return mState;
   }

   void InputAction::setState(EdgeState state)
   {
      mState = state;
   }
}//end of namespace mw
