/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputManager.h"

namespace mw
{
   InputManager* InputManager::_Instance = 0;

   InputManager* InputManager::instance()
   {
      if (_Instance == 0)
      {
         _Instance = new InputManager();
      }
      return _Instance;
   }

   InputAction* InputManager::createAction()
   {
      //FIXME:  This is not thread safe.
      InputAction* retval = new InputAction(mCounter);
      //retval->setID(mCounter);
      ++mCounter;
      return retval;
   }

}//end of namespace mw
