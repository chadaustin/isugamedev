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
 * File:          $RCSfile: InputManager.h,v $
 * Date modified: $Date: 2003-02-28 03:58:06 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_INPUT_MANAGER_H
#define SIREN_INPUT_MANAGER_H

#include <SDL.h>
#include <string>
#include <map>
#include "InputAction.h"

namespace siren
{
   /**
    * This class is the facade to the input abstraction. It provides a mapping
    * of string action names to a key press allowing the application to be
    * written independently of the knowledge of what keys have been pressed.
    */
   class SIREN_CLASS InputManager
   {
   public:
      ~InputManager();

      /**
       * Loads in input mappings from the given file and assigns the bindings
       * that it finds therein.
       *
       * @param filename      the file to read
       */
      void loadMappings(const std::string& filename);

      /**
       * Gets the input action associated with the given name ID. If the name is
       * not bound within this InputManager, a dummy input action is returned
       * with stubbed out input.
       *
       * @param name          the name of the action to get
       *
       * @return  the input action corresponding to the name
       */
      InputAction* getAction(const std::string& name);

      /**
       * Gets the action for the given key. If no action is mapped to the key, a
       * dummy input action is returned with stubbed out input.
       *
       * @param key           the key to get the action for
       *
       * @return  the input action corresponding to the key
       */
      InputAction* getAction(SDLKey key);

      /**
       * Gets the action for the given mouse button. If no action is mapped to
       * the button, a dummy input action is returned with stubbed out input.
       *
       * @param button        the button to get the action for
       *
       * @return  the input actiont corresponding to the button
       */
      InputAction* getAction(Uint8 button);

      /**
       * Gets the key bound to the action with the given name.
       *
       * @param name          the name of the action to query
       *
       * @return  the bound key; SDLK_UNKNOWN if not bound
       */
      SDLKey getKey(const std::string& name);

      /**
       * Gets the button bound to the action with the given name.
       *
       * @param name          the name of the action to query
       *
       * @return  the bound button; 0 if not bound
       */
      Uint8 getButton(const std::string& name);

      /**
       * This method must be called each frame with the appropriate time delta
       * since the last update. This will refresh the data in all the input
       * actions in this input manager.
       *
       * @param dt            time since the last update in seconds
       */
      void update(float dt);

      /**
       * This method must be called each time a key is pressed or released so
       * that the input actions can be updated appropriately.
       *
       * @param key           the key whose state has changed
       * @param down          true if the key is down; false if up
       */
      void onKeyPress(SDLKey key, bool down);

      /**
       * This methon must be called each time a mouse button is pressed or
       * released so that the input actions can be updated appropriately.
       *
       * @param button        the button whose state has changed
       * @param down          true if the button is down; false if up
       */
      void onMousePress(Uint8 button, bool down);

   private:
      // action name -> InputAction
      typedef std::map<std::string, InputAction*> ActionMap;
      ActionMap mActions;

      // key -> action name
      typedef std::map<SDLKey, std::string> KeyMap;
      KeyMap mKeys;

      // button -> action name
      typedef std::map<Uint8, std::string> ButtonMap;
      ButtonMap mButtons;
   };
}

#endif
