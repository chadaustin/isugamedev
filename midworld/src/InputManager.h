/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INPUT_MANAGER__H
#define MW_INPUT_MANAGER__H

#include <SDL.h>
#include "InputBinder.h"
#include "InputAction.h"

namespace mw
{
   /**
    * This class manages all InputActions; use this class to create all actions.
    */
   class InputManager
   {
   public:
      /**
       * Gets the instance of this Singleton
       * @return the instance of this Singleton
       */
      static InputManager* instance();

      /**
       * Creates a new InputAction for use.
       * @return a new InputAction object.
       */
      InputAction* createAction();
         
   protected:
      InputManager()
         : mCounter(1)
      {
      }
   private:
      ///The instance of this class
      static InputManager* _Instance;
      ///Counter for the register ids
      unsigned long mCounter;
   };


}//end of namespace mw
#endif
