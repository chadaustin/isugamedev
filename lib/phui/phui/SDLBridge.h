#ifndef PHUI_SDL_BRIDGE_H
#define PHUI_SDL_BRIDGE_H


#include <SDL/SDL.h>
#include "Input.h"


namespace phui {

   InputKey SDLToPhuiKey(SDLKey key);
   InputButton SDLToPhuiButton(Uint8 button);

}


#endif
