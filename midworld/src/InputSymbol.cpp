/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include <map>
#include <stdexcept>
#include "InputSymbol.h"

namespace mw
{
   // Our keymap type from string to SDLkey
   typedef std::map<std::string, SDLKey> KeyMap;

   namespace
   {
      /// Our key mappings
      static KeyMap gKeys;

      /**
       * This class inits the list of SDLKey mappings upon construction.
       */
      class SDLKeyInit
      {
      public:
         SDLKeyInit()
         {
            gKeys["KEY_ESCAPE"]     = SDLK_ESCAPE;
            gKeys["KEY_F1"]         = SDLK_F1;
            gKeys["KEY_F2"]         = SDLK_F2;
            gKeys["KEY_F3"]         = SDLK_F3;
            gKeys["KEY_F4"]         = SDLK_F4;
            gKeys["KEY_F5"]         = SDLK_F5;
            gKeys["KEY_F6"]         = SDLK_F6;
            gKeys["KEY_F7"]         = SDLK_F7;
            gKeys["KEY_F8"]         = SDLK_F8;
            gKeys["KEY_F9"]         = SDLK_F9;
            gKeys["KEY_F10"]        = SDLK_F10;
            gKeys["KEY_F11"]        = SDLK_F11;
            gKeys["KEY_F12"]        = SDLK_F12;
            gKeys["KEY_F13"]        = SDLK_F13;
            gKeys["KEY_F14"]        = SDLK_F14;
            gKeys["KEY_F15"]        = SDLK_F15;
            gKeys["KEY_TILDE"]      = SDLK_BACKQUOTE;
            gKeys["KEY_MINUS"]      = SDLK_MINUS;
            gKeys["KEY_EQUALS"]     = SDLK_EQUALS;
            gKeys["KEY_BACKSPACE"]  = SDLK_BACKSPACE;
            gKeys["KEY_TAB"]        = SDLK_TAB;
            gKeys["KEY_A"]          = SDLK_a;
            gKeys["KEY_B"]          = SDLK_b;
            gKeys["KEY_C"]          = SDLK_c;
            gKeys["KEY_D"]          = SDLK_d;
            gKeys["KEY_E"]          = SDLK_e;
            gKeys["KEY_F"]          = SDLK_f;
            gKeys["KEY_G"]          = SDLK_g;
            gKeys["KEY_H"]          = SDLK_h;
            gKeys["KEY_I"]          = SDLK_i;
            gKeys["KEY_J"]          = SDLK_j;
            gKeys["KEY_K"]          = SDLK_k;
            gKeys["KEY_L"]          = SDLK_l;
            gKeys["KEY_M"]          = SDLK_m;
            gKeys["KEY_N"]          = SDLK_n;
            gKeys["KEY_O"]          = SDLK_o;
            gKeys["KEY_P"]          = SDLK_p;
            gKeys["KEY_Q"]          = SDLK_q;
            gKeys["KEY_R"]          = SDLK_r;
            gKeys["KEY_S"]          = SDLK_s;
            gKeys["KEY_T"]          = SDLK_t;
            gKeys["KEY_U"]          = SDLK_u;
            gKeys["KEY_V"]          = SDLK_v;
            gKeys["KEY_W"]          = SDLK_w;
            gKeys["KEY_X"]          = SDLK_x;
            gKeys["KEY_Y"]          = SDLK_y;
            gKeys["KEY_Z"]          = SDLK_z;
            gKeys["KEY_0"]          = SDLK_0;
            gKeys["KEY_1"]          = SDLK_1;
            gKeys["KEY_2"]          = SDLK_2;
            gKeys["KEY_3"]          = SDLK_3;
            gKeys["KEY_4"]          = SDLK_4;
            gKeys["KEY_5"]          = SDLK_5;
            gKeys["KEY_6"]          = SDLK_6;
            gKeys["KEY_7"]          = SDLK_7;
            gKeys["KEY_8"]          = SDLK_8;
            gKeys["KEY_9"]          = SDLK_9;
            gKeys["KEY_KP0"]        = SDLK_KP0;
            gKeys["KEY_KP1"]        = SDLK_KP1;
            gKeys["KEY_KP2"]        = SDLK_KP2;
            gKeys["KEY_KP3"]        = SDLK_KP3;
            gKeys["KEY_KP4"]        = SDLK_KP4;
            gKeys["KEY_KP5"]        = SDLK_KP5;
            gKeys["KEY_KP6"]        = SDLK_KP6;
            gKeys["KEY_KP7"]        = SDLK_KP7;
            gKeys["KEY_KP8"]        = SDLK_KP8;
            gKeys["KEY_KP9"]        = SDLK_KP9;
            gKeys["KEY_SHIFT"]      = SDLK_LSHIFT;
            gKeys["KEY_CTRL"]       = SDLK_LCTRL;
            gKeys["KEY_ALT"]        = SDLK_LALT;
            gKeys["KEY_SPACE"]      = SDLK_SPACE;
            gKeys["KEY_OPENBRACE"]  = SDLK_LEFTBRACKET;
            gKeys["KEY_CLOSEBRACE"] = SDLK_RIGHTBRACKET;
            gKeys["KEY_SEMICOLON"]  = SDLK_SEMICOLON;
            gKeys["KEY_APOSTROPHE"] = SDLK_QUOTE;
            gKeys["KEY_COMMA"]      = SDLK_COMMA;
            gKeys["KEY_PERIOD"]     = SDLK_PERIOD;
            gKeys["KEY_SLASH"]      = SDLK_SLASH;
            gKeys["KEY_BACKSLASH"]  = SDLK_BACKSLASH;
            gKeys["KEY_ENTER"]      = SDLK_RETURN;
            gKeys["KEY_INSERT"]     = SDLK_INSERT;
            gKeys["KEY_DELETE"]     = SDLK_DELETE;
            gKeys["KEY_HOME"]       = SDLK_HOME;
            gKeys["KEY_END"]        = SDLK_END;
            gKeys["KEY_PAGE_UP"]    = SDLK_PAGEUP;
            gKeys["KEY_PAGE_DOWN"]  = SDLK_PAGEDOWN;
            gKeys["KEY_UP"]         = SDLK_UP;
            gKeys["KEY_DOWN"]       = SDLK_DOWN;
            gKeys["KEY_LEFT"]       = SDLK_LEFT;
            gKeys["KEY_RIGHT"]      = SDLK_RIGHT;
         }
      };

      static SDLKeyInit initKeys;
   }

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
      KeyMap::iterator itr = gKeys.find(name);
      if (itr != gKeys.end())
      {
         return itr->second;
      }
      else
      {
         return SDLK_UNKNOWN;
      }
   }

   const std::string& SDLKeyToString(const SDLKey& key)
   {
      for (KeyMap::iterator itr = gKeys.begin(); itr != gKeys.end(); ++itr)
      {
         if (itr->second == key)
         {
            return itr->first;
         }
      }

      // Couldn't find a match
      throw std::runtime_error("Couldn't find a name for the given SDL key");
   }
}
