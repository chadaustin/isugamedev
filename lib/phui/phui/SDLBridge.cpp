/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * File:          $RCSfile: SDLBridge.cpp,v $
 * Date modified: $Date: 2005-01-25 17:28:51 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include "SDLBridge.h"

namespace phui
{
   InputKey SDLToPhuiKey(SDLKey key) {
      if (key >= SDLK_0 && key <= SDLK_9) {
         return (InputKey)(KEY_0 + key - SDLK_0);
      }
      if (key >= SDLK_a && key <= SDLK_z) {
         return (InputKey)(KEY_A + key - SDLK_a);
      }
      // SDL supports up to F15, but we don't
      if (key >= SDLK_F1 && key <= SDLK_F12) {
         return (InputKey)(KEY_F1 + key - SDLK_F1);
      }
      if (key >= SDLK_KP0 && key <= SDLK_KP9) {
         return (InputKey)(KEY_0 + key - SDLK_KP0);
      }

      switch (key) {
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

   InputButton SDLToPhuiButton(Uint8 button) {
      switch (button) {
         case SDL_BUTTON_LEFT:   return BUTTON_LEFT;
         case SDL_BUTTON_MIDDLE: return BUTTON_MIDDLE;
         case SDL_BUTTON_RIGHT:  return BUTTON_RIGHT;
         default:                return BUTTON_UNKNOWN;
      }
   }
}
