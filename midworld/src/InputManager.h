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
 * File:          $RCSfile: InputManager.h,v $
 * Date modified: $Date: 2002-11-26 01:56:08 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_INPUT_MANAGER_H
#define MW_INPUT_MANAGER_H

#include <SDL.h>
#include <string>
#include <map>

namespace mw
{
   class InputAction;

   class InputManager
   {
   public:
      ~InputManager();
   
      void loadMappings(const std::string& filename);
      InputAction* getAction(const std::string& name);
      InputAction* getAction(SDLKey key);
      InputAction* getAction(Uint8 button);
      
      /// called once every frame
      void update(float dt);
      void onKeyPress(SDLKey key, bool down);
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
