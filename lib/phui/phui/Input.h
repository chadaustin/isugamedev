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
 * File:          $RCSfile: Input.h,v $
 * Date modified: $Date: 2005-01-23 21:46:47 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_INPUT_H
#define PHUI_INPUT_H

namespace phui
{
   enum InputButton
   {
      BUTTON_LEFT,
      BUTTON_MIDDLE,
      BUTTON_RIGHT,
      BUTTON_WHEEL_UP,
      BUTTON_WHEEL_DOWN,

      BUTTON_UNKNOWN,
   };

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
      KEY_KEYPAD_0,
      KEY_KEYPAD_1,
      KEY_KEYPAD_2,
      KEY_KEYPAD_3,
      KEY_KEYPAD_4,
      KEY_KEYPAD_5,
      KEY_KEYPAD_6,
      KEY_KEYPAD_7,
      KEY_KEYPAD_8,
      KEY_KEYPAD_9,
      KEY_KEYPAD_PERIOD,
      KEY_KEYPAD_PLUS,
      KEY_KEYPAD_MINUS,
      KEY_KEYPAD_DIVIDE,
      KEY_KEYPAD_MULTIPLY,
      KEY_KEYPAD_EQUALS,
      KEY_KEYPAD_ENTER,
      KEY_SHIFT,
      KEY_CTRL,
      KEY_ALT,
      KEY_WINDOWS,
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
      KEY_PRINTSCREEN,
      KEY_PAUSE,
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
}

#endif
