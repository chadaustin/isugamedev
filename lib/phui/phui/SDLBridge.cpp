#include "SDLBridge.h"


namespace phui {

   InputKey SDLToPhuiKey(SDLKey key) {
      switch (key) {
         default: return KEY_UNKNOWN;
      }
   }

   InputButton SDLToPhuiButton(Uint8 button) {
      switch (button) {
         case SDL_BUTTON_LEFT:   return BUTTON_LEFT;
         case SDL_BUTTON_MIDDLE: return BUTTON_MIDDLE;
         case SDL_BUTTON_RIGHT:  return BUTTON_RIGHT;
         default:                return BUTTON_UNKNOWN;
      }
   }

}
