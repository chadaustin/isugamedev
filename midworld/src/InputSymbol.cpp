/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "InputSymbol.h"

namespace mw
{
   InputKey SDLtoISym(const SDLKey key)
   {
      if (key >= SDLK_0 && key <= SDLK_9) 
      {
         return (InputKey)(KEY_0 + key - SDLK_0);
      }
      if (key >= SDLK_a && key <= SDLK_z) 
      {
         return (InputKey)(KEY_A + key - SDLK_a);
      }
      if (key >= SDLK_F1 && key <= SDLK_F15) 
      {
         return (InputKey)(KEY_F1 + key - SDLK_F1);
      }
      if (key >= SDLK_KP0 && key <= SDLK_KP9) 
      {
         return (InputKey)(KEY_KP0 + key - SDLK_KP0);
      }

      switch (key) 
      {
         case SDLK_BACKSPACE:    return KEY_BACKSPACE;
         case SDLK_TAB:          return KEY_TAB;
         case SDLK_CLEAR:        break;
         case SDLK_RETURN:       return KEY_ENTER;
         case SDLK_PAUSE:        break;
         case SDLK_ESCAPE:       return KEY_ESCAPE;
         case SDLK_SPACE:        return KEY_SPACE;
         case SDLK_EXCLAIM:      return KEY_1;
         case SDLK_QUOTEDBL:     return KEY_APOSTROPHE;
         case SDLK_HASH:         return KEY_3;
         case SDLK_DOLLAR:       return KEY_4;
         case SDLK_AMPERSAND:    return KEY_7;
         case SDLK_QUOTE:        return KEY_APOSTROPHE;
         case SDLK_LEFTPAREN:    return KEY_9;
         case SDLK_RIGHTPAREN:   return KEY_0;
         case SDLK_ASTERISK:     return KEY_8;
         case SDLK_PLUS:         return KEY_EQUALS;
         case SDLK_MINUS:        return KEY_MINUS;
         case SDLK_PERIOD:       return KEY_PERIOD;
         case SDLK_SLASH:        return KEY_SLASH;
         case SDLK_COLON:        return KEY_SEMICOLON;
         case SDLK_SEMICOLON:    return KEY_SEMICOLON;
         case SDLK_LESS:         return KEY_COMMA;
         case SDLK_EQUALS:       return KEY_EQUALS;
         case SDLK_GREATER:      return KEY_PERIOD;
         case SDLK_QUESTION:     return KEY_SLASH;
         case SDLK_AT:           return KEY_2;
         case SDLK_LEFTBRACKET:  return KEY_OPENBRACE;
         case SDLK_BACKSLASH:    return KEY_BACKSLASH;
         case SDLK_RIGHTBRACKET: return KEY_CLOSEBRACE;
         case SDLK_CARET:        return KEY_6;
         case SDLK_UNDERSCORE:   return KEY_MINUS;
         case SDLK_BACKQUOTE:    return KEY_TILDE;
         case SDLK_DELETE:       return KEY_DELETE;
         case SDLK_KP_PERIOD:    return KEY_UNKNOWN;
         case SDLK_KP_DIVIDE:    return KEY_UNKNOWN;
         case SDLK_KP_MULTIPLY:  return KEY_UNKNOWN;
         case SDLK_KP_MINUS:     return KEY_UNKNOWN;
         case SDLK_KP_PLUS:      return KEY_UNKNOWN;
         case SDLK_KP_ENTER:     return KEY_UNKNOWN;
         case SDLK_KP_EQUALS:    return KEY_UNKNOWN;
         case SDLK_UP:           return KEY_UP;
         case SDLK_DOWN:         return KEY_DOWN;
         case SDLK_RIGHT:        return KEY_RIGHT;
         case SDLK_LEFT:         return KEY_LEFT;
         case SDLK_INSERT:       return KEY_INSERT;
         case SDLK_HOME:         return KEY_HOME;
         case SDLK_END:          return KEY_END;
         case SDLK_PAGEUP:       return KEY_PAGE_UP;
         case SDLK_PAGEDOWN:     return KEY_PAGE_DOWN;
         case SDLK_NUMLOCK:      return KEY_UNKNOWN;
         case SDLK_CAPSLOCK:     return KEY_UNKNOWN;
         case SDLK_SCROLLOCK:    return KEY_UNKNOWN;
         case SDLK_RSHIFT:       return KEY_SHIFT;
         case SDLK_LSHIFT:       return KEY_SHIFT;
         case SDLK_RCTRL:        return KEY_CTRL;
         case SDLK_LCTRL:        return KEY_CTRL;
         case SDLK_RALT:         return KEY_ALT;
         case SDLK_LALT:         return KEY_ALT;
         case SDLK_RMETA:        return KEY_UNKNOWN;
         case SDLK_LMETA:        return KEY_UNKNOWN;
         case SDLK_LSUPER:       return KEY_UNKNOWN;
         case SDLK_RSUPER:       return KEY_UNKNOWN;
         case SDLK_MODE:         return KEY_UNKNOWN;
         case SDLK_HELP:         return KEY_UNKNOWN;
         case SDLK_PRINT:        return KEY_UNKNOWN;
         case SDLK_SYSREQ:       return KEY_UNKNOWN;
         case SDLK_BREAK:        return KEY_UNKNOWN;
         case SDLK_MENU:         return KEY_UNKNOWN;
         case SDLK_POWER:        return KEY_UNKNOWN;
         case SDLK_EURO:         return KEY_UNKNOWN;
      }
      return KEY_UNKNOWN;
   }

   InputKey StringtoISym(const std::string &name)
   {
      if (name == "KEY_ESCAPE")
      {
         return KEY_ESCAPE;
      }
      else if (name == "KEY_F1")
      {
         return KEY_F1;
      }
      else if (name == "KEY_F2")
      {
         return KEY_F2;
      }
      else if (name == "KEY_F3")
      {
         return KEY_F3;
      }
      else if (name == "KEY_F4")
      {
         return KEY_F4;
      }
      else if (name == "KEY_F5")
      {
         return KEY_F5;
      }
      else if (name == "KEY_F6")
      {
         return KEY_F6;
      }
      else if (name == "KEY_F7")
      {
         return KEY_F7;
      }
      else if (name == "KEY_F8")
      {
         return KEY_F8;
      }
      else if (name == "KEY_F9")
      {
         return KEY_F9;
      }
      else if (name == "KEY_F10")
      {
         return KEY_F10;
      }
      else if (name == "KEY_F11")
      {
         return KEY_F11;
      }
      else if (name == "KEY_F12")
      {
         return KEY_F12;
      }
      else if (name == "KEY_F13")
      {
         return KEY_F13;
      }
      else if (name == "KEY_F14")
      {
         return KEY_F14;
      }
      else if (name == "KEY_F15")
      {
         return KEY_F15;
      }
      else if (name == "KEY_TILDE")
      {
         return KEY_TILDE;
      }
      else if (name == "KEY_MINUS")
      {
         return KEY_MINUS;
      }
      else if (name == "KEY_EQUALS")
      {
         return KEY_EQUALS;
      }
      else if (name == "KEY_BACKSPACE")
      {
         return KEY_BACKSPACE;
      }
      else if (name == "KEY_TAB")
      {
         return KEY_TAB;
      }
      else if (name == "KEY_A")
      {
         return KEY_A;
      }
      else if (name == "KEY_B")
      {
         return KEY_B;
      }
      else if (name == "KEY_C")
      {
         return KEY_C;
      }
      else if (name == "KEY_D")
      {
         return KEY_D;
      }
      else if (name == "KEY_E")
      {
         return KEY_E;
      }
      else if (name == "KEY_F")
      {
         return KEY_F;
      }
      else if (name == "KEY_G")
      {
         return KEY_G;
      }
      else if (name == "KEY_H")
      { 
         return KEY_H;
      }
      else if (name == "KEY_I")
      {
         return KEY_I;
      }
      else if (name == "KEY_J")
      {
         return KEY_J;
      }
      else if (name == "KEY_K")
      {
         return KEY_K;
      }
      else if (name == "KEY_L")
      {
         return KEY_L;
      }
      else if (name == "KEY_M")
      {
         return KEY_M;
      }
      else if (name == "KEY_N")
      {
         return KEY_N;
      }
      else if (name == "KEY_O")
      {
         return KEY_O;
      }
      else if (name == "KEY_P")
      {
         return KEY_P;
      }
      else if (name == "KEY_Q")
      {
         return KEY_Q;
      }
      else if (name == "KEY_R")
      {
         return KEY_R;
      }
      else if (name == "KEY_S")
      {
         return KEY_S;
      }
      else if (name == "KEY_T")
      {
         return KEY_T;
      }
      else if (name == "KEY_U")
      {
         return KEY_U;
      }
      else if (name == "KEY_V")
      {
         return KEY_V;
      }
      else if (name == "KEY_W")
      {
         return KEY_W;
      }
      else if (name == "KEY_X")
      {
         return KEY_X;
      }
      else if (name == "KEY_Y")
      {
         return KEY_Y;
      }
      else if (name == "KEY_Z")
      {
         return KEY_Z;
      }
      else if (name == "KEY_0")
      {
         return KEY_0;
      }
      else if (name == "KEY_1")
      {
         return KEY_1;
      }
      else if (name == "KEY_2")
      {
         return KEY_2;
      }
      else if (name == "KEY_3")
      {
         return KEY_3;
      }
      else if (name == "KEY_4")
      {
         return KEY_4;
      }
      else if (name == "KEY_5")
      {
         return KEY_5;
      }
      else if (name == "KEY_6")
      {
         return KEY_6;
      }
      else if (name == "KEY_7")
      {
         return KEY_7;
      }
      else if (name == "KEY_8")
      {
         return KEY_8;
      }
      else if (name == "KEY_9")
      {
         return KEY_9;
      }
      else if (name == "KEY_KP0")
      {
         return KEY_KP0;
      }
      else if (name == "KEY_KP1")
      {
         return KEY_KP1;
      }
      else if (name == "KEY_KP2")
      {
         return KEY_KP2;
      }
      else if (name == "KEY_KP3")
      {
         return KEY_KP3;
      }
      else if (name == "KEY_KP4")
      {
         return KEY_KP4;
      }
      else if (name == "KEY_KP5")
      {
         return KEY_KP5;
      }
      else if (name == "KEY_KP6")
      {
         return KEY_KP6;
      }
      else if (name == "KEY_KP7")
      {
         return KEY_KP7;
      }
      else if (name == "KEY_KP8")
      {
         return KEY_KP8;
      }
      else if (name == "KEY_KP9")
      {
         return KEY_KP9;
      }
      else if (name == "KEY_SHIFT")
      {
         return KEY_SHIFT;
      }
      else if (name == "KEY_CTRL")
      {
         return KEY_CTRL;
      }
      else if (name == "KEY_ALT")
      {
         return KEY_ALT;
      }
      else if (name == "KEY_SPACE")
      {
         return KEY_SPACE;
      }
      else if (name == "KEY_OPENBRACE")
      {
         return KEY_OPENBRACE;
      }
      else if (name == "KEY_CLOSEBRACE")
      {
         return KEY_CLOSEBRACE;
      }
      else if (name == "KEY_SEMICOLON")
      {
         return KEY_SEMICOLON;
      }
      else if (name == "KEY_APOSTROPHE")
      {
         return KEY_APOSTROPHE;
      }
      else if (name == "KEY_COMMA")
      {
         return KEY_COMMA;
      }
      else if (name == "KEY_PERIOD")
      {
         return KEY_PERIOD;
      }
      else if (name == "KEY_SLASH")
      {
         return KEY_SLASH;
      }
      else if (name == "KEY_BACKSLASH")
      {
         return KEY_BACKSLASH;
      }
      else if (name == "KEY_ENTER")
      {
         return KEY_ENTER;
      }
      else if (name == "KEY_INSERT")
      {
         return KEY_INSERT;
      }
      else if (name == "KEY_DELETE")
      {
         return KEY_DELETE;
      }
      else if (name == "KEY_HOME")
      {
         return KEY_HOME;
      }
      else if (name == "KEY_END")
      {
         return KEY_END;
      }
      else if (name == "KEY_PAGE_UP")
      {
         return KEY_PAGE_UP;
      }
      else if (name == "KEY_PAGE_DOWN")
      {
         return KEY_PAGE_DOWN;
      }
      else if (name == "KEY_UP")
      {
         return KEY_UP;
      }
      else if (name == "KEY_DOWN")
      {
         return KEY_DOWN;
      }
      else if (name == "KEY_LEFT")
      {
         return KEY_LEFT;
      }
      else if (name == "KEY_RIGHT")
      {
         return KEY_RIGHT;
      }
      else
      {
         return KEY_UNKNOWN;
      }
   }
}//end of namespace mw
