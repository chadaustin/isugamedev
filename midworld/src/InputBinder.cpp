/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputBinder.h"

namespace mw
{
   InputBinder* InputBinder::_Instance = 0;

   InputBinder* InputBinder::instance()
   {
      if (_Instance == 0)
      {
         _Instance = new InputBinder();
      }
      return _Instance;
   }

   void InputBinder::bindAction(InputAction *action, const SDLKey &key)
   {
      mKeyMap[key] = action;
   }

   InputAction* InputBinder::getAction(const SDLKey &key)
   {
      std::map<SDLKey, InputAction*>::iterator itr;
      itr = mKeyMap.find(key);
      if (itr != mKeyMap.end())
      {
         return itr->second;
      }
      return NULL; 
   }
}//end of namespace mw
