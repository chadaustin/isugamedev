
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: Keyboard.h,v $
// Date modified: $Date: 2002-02-06 22:22:22 $
// Version:       $Revision: 1.12 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "gk/gkCommon.h"
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "gk/DigitalDevice.h"

/** Keyboard device driver for the GameInput system.
 *
 * Don't use this device directly (although you could, it isn't recommended).
 * Instead, use the DigitalInterface class
 * to access the button data in the Keyboard.  Using the Interface classes 
 * gives your application the ability to bind keys to event identifiers 
 * (keybinding).  If you use this class by itself, you will not get any kind 
 * of keybinding ability.
 *
 * <H3> TODO: </h3>
 * - need to add TextDevice support to this driver, and to the GameInput system
 *
 * @see Mouse
 * @see Joystick
 * @see DigitalDevice
 * @see Device
 */
class Keyboard : public DigitalDevice
{
public:
   /** Keyboard Buttons.
    * This is the list of keyboard identifiers you can use.
    * When binding keys in the GameInput class, you can 
    * prefix each of these with "KEY_"  (i.e. ESC would be "KEY_ESC").
    */
   enum Key
   {
      BELL = 7,
      BACKSPACE = 8,
      TAB = 9,
      NEWLINE = 10,
      VERTTAB = 11,
      FORMFEED = 12,
      CR = 13,
      ESC = 27,
      SPACE = 32,
      BANG = 33,
      DOUBLEQUOTES = 34,
      HASH = 35,
      DOLLAR = 36,
      PERCENT = 37,
      AMPERSAND = 38,
      RIGHTQUOTE = '\'',
      LEFTPAREN = 40,
      RIGHTPAREN = 41,
      ASTERISK = '*',
      POS = '+',
      COMMA = ',',
      NEG = '-',
      PERIOD = '.',
      SLASH = '/',
      ZERO = '0', ONE = '1', TWO = '2', THREE = '3', FOUR = '4', FIVE = '5',
      SIX = '6', SEVEN = '7', EIGHT = '8', NINE = '9',
      COLON = ':',
      SEMICOLON = ';',
      LESSTHAN = '<',
      EQUALS = '=',
      GREATERTHAN = '>',
      QUESTION = '?',
      AT = '@',
      A = 'A',B = 'B',C = 'C',D = 'D',E = 'E',F = 'F',G = 'G',H = 'H',
      I = 'I',J = 'J',K = 'K',L = 'L',M = 'M',N = 'N',O = 'O',P = 'P',Q = 'Q',
      R = 'R',S = 'S',T = 'T',U = 'U',V = 'V',W = 'W',X = 'X',Y = 'Y',Z = 'Z',
      LEFTBRACKET = '[',
      BACKSLASH = '\\',
      RIGHTBRACKET = ']',
      CARET = '^',
      UNDERSCORE = '_',
      LEFTQUOTE = '`',
      CURLYLEFT = '{',
      PIPE = '|',
      CURLYRIGHT = '}',
      TILDE = '~',
      DEL = 127,
      /////////////////////////////////////////////////////////////////
      PAGEUP = 256,
      PAGEDOWN = 257,
      HOME = 258,
      END = 259,
      INSERT = 260,
      UPARROW = 261,
      DOWNARROW = 262,
      LEFTARROW = 263,
      RIGHTARROW = 264,
      CAPS = 265,
      LSHIFT = 266,
      LCTRL = 267,
      RSHIFT = 268,
      RCTRL = 269,
      F1 = 270, F2 = 271, F3 = 272, F4 = 273, F5 = 274, F6 = 275,
      F7 = 276, F8 = 277, F9 = 278, F10 = 279, F11 = 280, F12 = 281,
      NumberOfKeys = 282 // make sure this number is bigger than the others.
   };

   /** constructor */
   Keyboard() : DigitalDevice()
   {
      this->setNumInputs( NumberOfKeys );
      initialize_map();
   }

   /** get the keys pressed since the last frame */
   std::vector<Key>& queue() { return mQueue; }

private:
   std::vector<Key> mQueue;

   void initialize_map()
   {
      mMap["KEY_BS"] = Keyboard::BACKSPACE;
      mMap["KEY_TAB"] = Keyboard::TAB;
      mMap["KEY_NEWLINE"] = Keyboard::NEWLINE;
      mMap["KEY_VERTTAB"] = Keyboard::VERTTAB;
      mMap["KEY_FORMFEED"] = Keyboard::FORMFEED;
      mMap["KEY_CR"] = Keyboard::CR;
      mMap["KEY_ESC"] = Keyboard::ESC;
      mMap["KEY_SPACE"] = Keyboard::SPACE;
      mMap["KEY_BANG"] = Keyboard::BANG;
      mMap["KEY_DOUBLEQUOTES"] = Keyboard::DOUBLEQUOTES;
      mMap["KEY_HASH"] = Keyboard::HASH;
      mMap["KEY_DOLLAR"] = Keyboard::DOLLAR;
      mMap["KEY_PERCENT"] = Keyboard::PERCENT;
      mMap["KEY_AMPERSAND"] = Keyboard::AMPERSAND;
      mMap["KEY_RIGHTQUOTE"] = Keyboard::RIGHTQUOTE;
      mMap["KEY_LEFTPAREN"] = Keyboard::LEFTPAREN;
      mMap["KEY_RIGHTPAREN"] = Keyboard::RIGHTPAREN;
      mMap["KEY_ASTERISK"] = Keyboard::ASTERISK;
      mMap["KEY_POS"] = Keyboard::POS;
      mMap["KEY_COMMA"] = Keyboard::COMMA;
      mMap["KEY_NEG"] = Keyboard::NEG;
      mMap["KEY_PERIOD"] = Keyboard::PERIOD;
      mMap["KEY_SLASH"] = Keyboard::SLASH;
      mMap["KEY_ZERO"] = Keyboard::ZERO;
      mMap["KEY_ONE"] = Keyboard::ONE;
      mMap["KEY_TWO"] = Keyboard::TWO;
      mMap["KEY_THREE"] = Keyboard::THREE;
      mMap["KEY_FOUR"] = Keyboard::FOUR;
      mMap["KEY_FIVE"] = Keyboard::FIVE;
      mMap["KEY_SIX"] = Keyboard::SIX;
      mMap["KEY_SEVEN"] = Keyboard::SEVEN;
      mMap["KEY_EIGHT"] = Keyboard::EIGHT;
      mMap["KEY_NINE"] = Keyboard::NINE;
      mMap["KEY_COLON"] = Keyboard::COLON;
      mMap["KEY_SEMICOLON"] = Keyboard::SEMICOLON;
      mMap["KEY_LESSTHAN"] = Keyboard::LESSTHAN;
      mMap["KEY_EQUALS"] = Keyboard::EQUALS;
      mMap["KEY_GREATERTHAN"] = Keyboard::GREATERTHAN;
      mMap["KEY_QUESTION"] = Keyboard::QUESTION;
      mMap["KEY_AT"] = Keyboard::AT;
      mMap["KEY_A"] = Keyboard::A;
      mMap["KEY_B"] = Keyboard::B;
      mMap["KEY_C"] = Keyboard::C;
      mMap["KEY_D"] = Keyboard::D;
      mMap["KEY_E"] = Keyboard::E;
      mMap["KEY_F"] = Keyboard::F;
      mMap["KEY_G"] = Keyboard::G;
      mMap["KEY_H"] = Keyboard::H;
      mMap["KEY_I"] = Keyboard::I;
      mMap["KEY_J"] = Keyboard::J;
      mMap["KEY_K"] = Keyboard::K;
      mMap["KEY_L"] = Keyboard::L;
      mMap["KEY_M"] = Keyboard::M;
      mMap["KEY_N"] = Keyboard::N;
      mMap["KEY_O"] = Keyboard::O;
      mMap["KEY_P"] = Keyboard::P;
      mMap["KEY_Q"] = Keyboard::Q;
      mMap["KEY_R"] = Keyboard::R;
      mMap["KEY_S"] = Keyboard::S;
      mMap["KEY_T"] = Keyboard::T;
      mMap["KEY_U"] = Keyboard::U;
      mMap["KEY_V"] = Keyboard::V;
      mMap["KEY_W"] = Keyboard::W;
      mMap["KEY_X"] = Keyboard::X;
      mMap["KEY_Y"] = Keyboard::Y;
      mMap["KEY_Z"] = Keyboard::Z;
      mMap["KEY_LEFTBRACKET"] = Keyboard::LEFTBRACKET;
      mMap["KEY_BACKSLASH"] = Keyboard::BACKSLASH;
      mMap["KEY_RIGHTBRACKET"] = Keyboard::RIGHTBRACKET;
      mMap["KEY_CARET"] = Keyboard::CARET;
      mMap["KEY_UNDERSCORE"] = Keyboard::UNDERSCORE;
      mMap["KEY_LEFTQUOTE"] = Keyboard::LEFTQUOTE;
      mMap["KEY_CURLYLEFT"] = Keyboard::CURLYLEFT;
      mMap["KEY_PIPE"] = Keyboard::PIPE;
      mMap["KEY_CURLYRIGHT"] = Keyboard::CURLYRIGHT;
      mMap["KEY_TILDE"] = Keyboard::TILDE;
      mMap["KEY_DEL"] = Keyboard::DEL;
      mMap["KEY_PAGEUP"] = Keyboard::PAGEUP;
      mMap["KEY_PAGEDOWN"] = Keyboard::PAGEDOWN;
      mMap["KEY_HOME"] = Keyboard::HOME;
      mMap["KEY_END"] = Keyboard::END;
      mMap["KEY_INSERT"] = Keyboard::INSERT;
      mMap["KEY_UPARROW"] = Keyboard::UPARROW;
      mMap["KEY_DOWNARROW"] = Keyboard::DOWNARROW;
      mMap["KEY_LEFTARROW"] = Keyboard::LEFTARROW;
      mMap["KEY_RIGHTARROW"] = Keyboard::RIGHTARROW;
      mMap["KEY_CAPS"] = Keyboard::CAPS;
      mMap["KEY_LSHIFT"] = Keyboard::LSHIFT;
      mMap["KEY_LCTRL"] = Keyboard::LCTRL;
      mMap["KEY_RSHIFT"] = Keyboard::RSHIFT;
      mMap["KEY_RCTRL"] = Keyboard::RCTRL;
      mMap["KEY_F1"] = Keyboard::F1;
      mMap["KEY_F2"] = Keyboard::F2;
      mMap["KEY_F3"] = Keyboard::F3;
      mMap["KEY_F4"] = Keyboard::F4;
      mMap["KEY_F5"] = Keyboard::F5;
      mMap["KEY_F6"] = Keyboard::F6;
      mMap["KEY_F7"] = Keyboard::F7;
      mMap["KEY_F8"] = Keyboard::F8;
      mMap["KEY_F9"] = Keyboard::F9;
      mMap["KEY_F10"] = Keyboard::F10;
      mMap["KEY_F11"] = Keyboard::F11;
      mMap["KEY_F12"] = Keyboard::F12;
   }
};


#endif
