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
