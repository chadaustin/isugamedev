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
 * File:          $RCSfile: InputBinder.h,v $
 * Date modified: $Date: 2002-11-03 05:35:10 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_INPUT_BINDER_H
#define MW_INPUT_BINDER_H

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
      static InputBinder& instance();
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
      /// This object is a singleton. Use InputBinder::instance() instead.
      InputBinder();

      ///@{
      ///  Not implemented on purpose to cause a compile-time error on usage.
      InputBinder(const InputBinder& binder);
      InputBinder& operator=(const InputBinder& binder);
      ///@}

   private:
      static InputBinder* mInstance;

      //@todo make this generic
      std::map<InputKey, InputAction*>mKeyMap;

   };
}

#endif
