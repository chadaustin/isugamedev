#include <fstream>
#include "InputAction.h"
#include "InputManager.h"
#include "InputSymbol.h"


namespace mw
{
   InputManager::~InputManager()
   {
      for (ActionMap::iterator i = mActions.begin(); i != mActions.end(); ++i)
      {
         delete i->second;
      }
   }

   void InputManager::loadMappings(const std::string& filename)
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
   
   InputAction* InputManager::getAction(const std::string& name)
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
   
   InputAction* InputManager::getAction(SDLKey key)
   {
      return getAction(mKeys[key]);
   }
   
   InputAction* InputManager::getAction(Uint8 button)
   {
      return getAction(mButtons[button]);
   }
   
   void InputManager::update(float dt)
   {
      for (ActionMap::iterator i = mActions.begin(); i != mActions.end(); ++i)
      {
         i->second->update(dt);
      }
   }
   
   void InputManager::onKeyPress(SDLKey key, bool down)
   {
      getAction(key)->onPress(down);
   }
   
   void InputManager::onMousePress(Uint8 button, bool down)
   {
      getAction(button)->onPress(down);
   }
}
