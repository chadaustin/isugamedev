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
 * File:          $RCSfile: InputManager.cpp,v $
 * Date modified: $Date: 2003-01-02 08:04:50 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <fstream>
#include "InputAction.h"
#include "InputManager.h"
#include "InputSymbol.h"

namespace siren
{
   InputManager::~InputManager()
   {
      for (ActionMap::iterator i = mActions.begin(); i != mActions.end(); ++i)
      {
         delete i->second;
      }
   }

   void
   InputManager::loadMappings(const std::string& filename)
   {
      std::ifstream in(filename.c_str());
      while (in)
      {
         std::string buffer;
         std::getline(in, buffer);
         int index = buffer.find('=');
         if (index != -1)
         {
            std::string key = buffer.substr(0, index);
            std::string action = buffer.substr(index + 1);
            
            if (isMouseSymbol(key))
            {
               mButtons[stringToSDLButton(key)] = action;
            }
            else
            {
               mKeys[stringToSDLKey(key)] = action;
            }
         }
      }
   }
   
   InputAction*
   InputManager::getAction(const std::string& name)
   {
      InputAction* i = mActions[name];
      if (i)
      {
         return i;
      }
      else
      {
         InputAction* action = new InputAction();
         mActions[name] = action;
         return action;
      }
   }
   
   InputAction*
   InputManager::getAction(SDLKey key)
   {
      return getAction(mKeys[key]);
   }
   
   InputAction*
   InputManager::getAction(Uint8 button)
   {
      return getAction(mButtons[button]);
   }

   SDLKey InputManager::getKey(const std::string& name)
   {
      for(KeyMap::iterator itr=mKeys.begin(); itr != mKeys.end(); ++itr)
      {
         if(itr->second == name)
            return itr->first;
      }
      return SDLK_UNKNOWN;
   }

   Uint8 InputManager::getButton(const std::string& name)
   {
      for(ButtonMap::iterator itr=mButtons.begin(); itr != mButtons.end(); ++itr)
      {
         if(itr->second == name)
            return itr->first;
      }
      return 0;
   }
   
   void
   InputManager::update(float dt)
   {
      for (ActionMap::iterator i = mActions.begin(); i != mActions.end(); ++i)
      {
         i->second->update(dt);
      }
   }
   
   void
   InputManager::onKeyPress(SDLKey key, bool down)
   {
      getAction(key)->onPress(down);
   }
   
   void
   InputManager::onMousePress(Uint8 button, bool down)
   {
      getAction(button)->onPress(down);
   }
}
