/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputSymbol.h"

namespace mw
{
   bool isMouseSymbol(const std::string& symbol)
   {
      return (symbol == "MOUSE_LEFT" ||
              symbol == "MOUSE_RIGHT" ||
              symbol == "MOUSE_MIDDLE");
   }
   
   Uint8 stringToSDLButton(const std::string& symbol)
   {
      if (symbol == "MOUSE_LEFT")
      {
         return SDL_BUTTON_LEFT;
      }
      else if (symbol == "MOUSE_RIGHT")
      {
         return SDL_BUTTON_RIGHT;
      }
      else if (symbol == "MOUSE_MIDDLE")
      {
         return SDL_BUTTON_MIDDLE;
      }
      else
      {
         return 0;
      }
   }

   SDLKey stringToSDLKey(const std::string& name)
   {
      if (name == "KEY_ESCAPE")
      {
         return SDLK_ESCAPE;
      }
      else if (name == "KEY_F1")
      {
         return SDLK_F1;
      }
      else if (name == "KEY_F2")
      {
         return SDLK_F2;
      }
      else if (name == "KEY_F3")
      {
         return SDLK_F3;
      }
      else if (name == "KEY_F4")
      {
         return SDLK_F4;
      }
      else if (name == "KEY_F5")
      {
         return SDLK_F5;
      }
      else if (name == "KEY_F6")
      {
         return SDLK_F6;
      }
      else if (name == "KEY_F7")
      {
         return SDLK_F7;
      }
      else if (name == "KEY_F8")
      {
         return SDLK_F8;
      }
      else if (name == "KEY_F9")
      {
         return SDLK_F9;
      }
      else if (name == "KEY_F10")
      {
         return SDLK_F10;
      }
      else if (name == "KEY_F11")
      {
         return SDLK_F11;
      }
      else if (name == "KEY_F12")
      {
         return SDLK_F12;
      }
      else if (name == "KEY_F13")
      {
         return SDLK_F13;
      }
      else if (name == "KEY_F14")
      {
         return SDLK_F14;
      }
      else if (name == "KEY_F15")
      {
         return SDLK_F15;
      }
      else if (name == "KEY_TILDE")
      {
         return SDLK_BACKQUOTE;
      }
      else if (name == "KEY_MINUS")
      {
         return SDLK_MINUS;
      }
      else if (name == "KEY_EQUALS")
      {
         return SDLK_EQUALS;
      }
      else if (name == "KEY_BACKSPACE")
      {
         return SDLK_BACKSPACE;
      }
      else if (name == "KEY_TAB")
      {
         return SDLK_TAB;
      }
      else if (name == "KEY_A")
      {
         return SDLK_a;
      }
      else if (name == "KEY_B")
      {
         return SDLK_b;
      }
      else if (name == "KEY_C")
      {
         return SDLK_c;
      }
      else if (name == "KEY_D")
      {
         return SDLK_d;
      }
      else if (name == "KEY_E")
      {
         return SDLK_e;
      }
      else if (name == "KEY_F")
      {
         return SDLK_f;
      }
      else if (name == "KEY_G")
      {
         return SDLK_g;
      }
      else if (name == "KEY_H")
      { 
         return SDLK_h;
      }
      else if (name == "KEY_I")
      {
         return SDLK_i;
      }
      else if (name == "KEY_J")
      {
         return SDLK_j;
      }
      else if (name == "KEY_K")
      {
         return SDLK_k;
      }
      else if (name == "KEY_L")
      {
         return SDLK_l;
      }
      else if (name == "KEY_M")
      {
         return SDLK_m;
      }
      else if (name == "KEY_N")
      {
         return SDLK_n;
      }
      else if (name == "KEY_O")
      {
         return SDLK_o;
      }
      else if (name == "KEY_P")
      {
         return SDLK_p;
      }
      else if (name == "KEY_Q")
      {
         return SDLK_q;
      }
      else if (name == "KEY_R")
      {
         return SDLK_r;
      }
      else if (name == "KEY_S")
      {
         return SDLK_s;
      }
      else if (name == "KEY_T")
      {
         return SDLK_t;
      }
      else if (name == "KEY_U")
      {
         return SDLK_u;
      }
      else if (name == "KEY_V")
      {
         return SDLK_v;
      }
      else if (name == "KEY_W")
      {
         return SDLK_w;
      }
      else if (name == "KEY_X")
      {
         return SDLK_x;
      }
      else if (name == "KEY_Y")
      {
         return SDLK_y;
      }
      else if (name == "KEY_Z")
      {
         return SDLK_z;
      }
      else if (name == "KEY_0")
      {
         return SDLK_0;
      }
      else if (name == "KEY_1")
      {
         return SDLK_1;
      }
      else if (name == "KEY_2")
      {
         return SDLK_2;
      }
      else if (name == "KEY_3")
      {
         return SDLK_3;
      }
      else if (name == "KEY_4")
      {
         return SDLK_4;
      }
      else if (name == "KEY_5")
      {
         return SDLK_5;
      }
      else if (name == "KEY_6")
      {
         return SDLK_6;
      }
      else if (name == "KEY_7")
      {
         return SDLK_7;
      }
      else if (name == "KEY_8")
      {
         return SDLK_8;
      }
      else if (name == "KEY_9")
      {
         return SDLK_9;
      }
      else if (name == "KEY_KP0")
      {
         return SDLK_KP0;
      }
      else if (name == "KEY_KP1")
      {
         return SDLK_KP1;
      }
      else if (name == "KEY_KP2")
      {
         return SDLK_KP2;
      }
      else if (name == "KEY_KP3")
      {
         return SDLK_KP3;
      }
      else if (name == "KEY_KP4")
      {
         return SDLK_KP4;
      }
      else if (name == "KEY_KP5")
      {
         return SDLK_KP5;
      }
      else if (name == "KEY_KP6")
      {
         return SDLK_KP6;
      }
      else if (name == "KEY_KP7")
      {
         return SDLK_KP7;
      }
      else if (name == "KEY_KP8")
      {
         return SDLK_KP8;
      }
      else if (name == "KEY_KP9")
      {
         return SDLK_KP9;
      }
      else if (name == "KEY_SHIFT")
      {
         return SDLK_LSHIFT;
      }
      else if (name == "KEY_CTRL")
      {
         return SDLK_LCTRL;
      }
      else if (name == "KEY_ALT")
      {
         return SDLK_LALT;
      }
      else if (name == "KEY_SPACE")
      {
         return SDLK_SPACE;
      }
      else if (name == "KEY_OPENBRACE")
      {
         return SDLK_LEFTBRACKET;
      }
      else if (name == "KEY_CLOSEBRACE")
      {
         return SDLK_RIGHTBRACKET;
      }
      else if (name == "KEY_SEMICOLON")
      {
         return SDLK_SEMICOLON;
      }
      else if (name == "KEY_APOSTROPHE")
      {
         return SDLK_QUOTE;
      }
      else if (name == "KEY_COMMA")
      {
         return SDLK_COMMA;
      }
      else if (name == "KEY_PERIOD")
      {
         return SDLK_PERIOD;
      }
      else if (name == "KEY_SLASH")
      {
         return SDLK_SLASH;
      }
      else if (name == "KEY_BACKSLASH")
      {
         return SDLK_BACKSLASH;
      }
      else if (name == "KEY_ENTER")
      {
         return SDLK_RETURN;
      }
      else if (name == "KEY_INSERT")
      {
         return SDLK_INSERT;
      }
      else if (name == "KEY_DELETE")
      {
         return SDLK_DELETE;
      }
      else if (name == "KEY_HOME")
      {
         return SDLK_HOME;
      }
      else if (name == "KEY_END")
      {
         return SDLK_END;
      }
      else if (name == "KEY_PAGE_UP")
      {
         return SDLK_PAGEUP;
      }
      else if (name == "KEY_PAGE_DOWN")
      {
         return SDLK_PAGEDOWN;
      }
      else if (name == "KEY_UP")
      {
         return SDLK_UP;
      }
      else if (name == "KEY_DOWN")
      {
         return SDLK_DOWN;
      }
      else if (name == "KEY_LEFT")
      {
         return SDLK_LEFT;
      }
      else if (name == "KEY_RIGHT")
      {
         return SDLK_RIGHT;
      }
      else
      {
         return SDLK_UNKNOWN;
      }
   }
}//end of namespace mw
