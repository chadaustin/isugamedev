/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INPUT_SYMBOL_H
#define MW_INPUT_SYMBOL_H

#include <SDL.h>
#include <string>

namespace mw
{
   /**
    * Symbols for all keyboard buttons
    */
   enum InputKey
   {
      KEY_ESCAPE,
      KEY_F1,
      KEY_F2,
      KEY_F3,
      KEY_F4,
      KEY_F5,
      KEY_F6,
      KEY_F7,
      KEY_F8,
      KEY_F9,
      KEY_F10,
      KEY_F11,
      KEY_F12,
      KEY_F13,
      KEY_F14,
      KEY_F15,
      KEY_TILDE,
      KEY_MINUS,
      KEY_EQUALS,
      KEY_BACKSPACE,
      KEY_TAB,
      KEY_A,
      KEY_B,
      KEY_C,
      KEY_D,
      KEY_E,
      KEY_F,
      KEY_G,
      KEY_H,
      KEY_I,
      KEY_J,
      KEY_K,
      KEY_L,
      KEY_M,
      KEY_N,
      KEY_O,
      KEY_P,
      KEY_Q,
      KEY_R,
      KEY_S,
      KEY_T,
      KEY_U,
      KEY_V,
      KEY_W,
      KEY_X,
      KEY_Y,
      KEY_Z,
      KEY_0,
      KEY_1,
      KEY_2,
      KEY_3,
      KEY_4,
      KEY_5,
      KEY_6,
      KEY_7,
      KEY_8,
      KEY_9,
      KEY_KP0,
      KEY_KP1,
      KEY_KP2,
      KEY_KP3,
      KEY_KP4,
      KEY_KP5,
      KEY_KP6,
      KEY_KP7,
      KEY_KP8,
      KEY_KP9,
      KEY_SHIFT,
      KEY_CTRL,
      KEY_ALT,
      KEY_SPACE,
      KEY_OPENBRACE,
      KEY_CLOSEBRACE,
      KEY_SEMICOLON,
      KEY_APOSTROPHE,
      KEY_COMMA,
      KEY_PERIOD,
      KEY_SLASH,
      KEY_BACKSLASH,
      KEY_ENTER,
      KEY_INSERT,
      KEY_DELETE,
      KEY_HOME,
      KEY_END,
      KEY_PAGE_UP,
      KEY_PAGE_DOWN,
      KEY_UP,
      KEY_RIGHT,
      KEY_DOWN,
      KEY_LEFT,

      KEY_UNKNOWN,
   };
   /**
    * Gets the Input Symbol key for the SDL key
    * @param key the SDLKey to get the symbol for
    * @return the Input Symbol key
    */
   InputKey SDLtoISym(const SDLKey key);
  
   /**
    * Gets the Input Symbol key for the std::string
    * @param name the name of the key to get
    * @return the Input Symbol key
    */
   InputKey StringtoISym(const std::string &name);

}//end of namespace mw
#endif
