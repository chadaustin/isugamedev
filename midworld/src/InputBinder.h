/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INPUT_BINDER__H
#define MW_INPUT_BINDER__H

#include <SDL.h>
#include <map>
#include <string>
#include "InputAction.h"
#include "InputParser.h"
#include "InputSymbol.h"

namespace mw
{
   /**
    * Binds an input to an action
    */
   class InputBinder
   {
   public:
      /**
       * This class is a Singleton
       */
      static InputBinder* instance();
      /**
       * Binds an SDL_Event to an InputAction
       * @param event the event to bind
       * @param action the action to bind
       */
      void bindAction(InputAction *action, const InputKey &key);
      /**
       * Gets the action from the SDLKey
       * @param key the key to retrieve an action for
       * @return the action which is bound to the key
       */
      InputAction* getAction(const InputKey &key);
      
   protected:
      InputBinder()
      {
      }
   private:
      static InputBinder* _Instance;
      //@todo make this generic
      std::map<InputKey, InputAction*>mKeyMap;

   };
}//end of namespace mw
#endif
