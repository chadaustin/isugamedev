/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputBinder.h"

namespace mw
{
   InputBinder* InputBinder::mInstance = 0;

   InputBinder::InputBinder()
   {}

   InputBinder& InputBinder::instance()
   {
      if (mInstance == 0)
      {
         mInstance = new InputBinder();
      }
      return *mInstance;
   }

   void InputBinder::bindAction(InputAction *action, const InputKey &key)
   {
      mKeyMap[key] = action;
   }

   InputAction* InputBinder::getAction(const InputKey &key)
   {
      return mKeyMap[key];
   }
}
