#ifndef MW_OPTIONS_STATE_H
#define MW_OPTIONS_STATE_H

#include <vector>
#include <gltext.h>
#include "State.h"
#include "Texture.h"
#include <string>
#include "InputManager.h"

namespace mw
{
   enum
   {
      KEY_UP=0,
      KEY_DOWN,
      KEY_LEFT,
      KEY_RIGHT,
      KEY_ZOOM_IN,
      KEY_ZOOM_OUT,
      KEY_PITCH_UP,
      KEY_PITCH_DOWN,
      KEY_YAW_LEFT,
      KEY_YAW_RIGHT,
      KEY_SHOOT,
      KEY_CYCLE_WEAPON,
      KEY_QUIT
   };
   class Application;

   class OptionsState : public State
   {
   public:
      OptionsState( Application* );

      ~OptionsState();

      void update(float dt) {}

      void draw();

      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y) {}

      private:
         gltext::Font* mFont;
         gltext::FontRenderer* mFontRenderer;
         std::vector<Texture*> mImages;
         SDLKey bindings[13];
         Uint8 mouseBindings[13];
         bool bindKey;
         int currentSelection;
         InputManager mInputManager;
         void writeConfigFile();
   };

   
}

#endif
