/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** isym-beg
 *
 * input sym - extendable symbols for keyboard/mouse/joy/etc...
 * input sym is (C) Copyright 2002 by Kevin Meinert, Chad Austin, Ben Scott
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
 ************************************************************** isym-end */

#ifndef INPUT_SYM_H
#define INPUT_SYM_H


namespace isym 
{
   /** @ingroup IsymAPI
    *  @{
    */
   
   /** Input symbol type.  
    *  Use this when creating new symbols and pointers to symbols.
    */
#ifdef WIN32
   typedef __uint64 Symbol;
#else
   typedef unsigned long long Symbol;
#endif
          
   /** Returns a unique identifier.
    *  Rolls around after calling 2^64 times.
    */
   Symbol getUID();
   
   /** @name input symbols
    *  @{
    */
          
   /** left mouse button... */
   const Symbol MOUSE_LEFT = isym::getUID();
   const Symbol MOUSE_MIDDLE = isym::getUID();
   const Symbol MOUSE_RIGHT = isym::getUID();
   const Symbol MOUSE_0 = MOUSE_LEFT;
   const Symbol MOUSE_1 = MOUSE_MIDDLE;
   const Symbol MOUSE_2 = MOUSE_RIGHT;
   const Symbol KEY_ESCAPE = isym::getUID();
   const Symbol KEY_F1 = isym::getUID();
   const Symbol KEY_F2 = isym::getUID();
   const Symbol KEY_F3 = isym::getUID();
   const Symbol KEY_F4 = isym::getUID();
   const Symbol KEY_F5 = isym::getUID();
   const Symbol KEY_F6 = isym::getUID();
   const Symbol KEY_F7 = isym::getUID();
   const Symbol KEY_F8 = isym::getUID();
   const Symbol KEY_F9 = isym::getUID();
   const Symbol KEY_F10 = isym::getUID();
   const Symbol KEY_F11 = isym::getUID();
   const Symbol KEY_F12 = isym::getUID();
   const Symbol KEY_TILDE = isym::getUID();
   const Symbol KEY_MINUS = isym::getUID();
   const Symbol KEY_EQUALS = isym::getUID();
   const Symbol KEY_BACKSPACE = isym::getUID();
   const Symbol KEY_TAB = isym::getUID();
   const Symbol KEY_A = isym::getUID();
   const Symbol KEY_B = isym::getUID();
   const Symbol KEY_C = isym::getUID();
   const Symbol KEY_D = isym::getUID();
   const Symbol KEY_E = isym::getUID();
   const Symbol KEY_F = isym::getUID();
   const Symbol KEY_G = isym::getUID();
   const Symbol KEY_H = isym::getUID();
   const Symbol KEY_I = isym::getUID();
   const Symbol KEY_J = isym::getUID();
   const Symbol KEY_K = isym::getUID();
   const Symbol KEY_L = isym::getUID();
   const Symbol KEY_M = isym::getUID();
   const Symbol KEY_N = isym::getUID();
   const Symbol KEY_O = isym::getUID();
   const Symbol KEY_P = isym::getUID();
   const Symbol KEY_Q = isym::getUID();
   const Symbol KEY_R = isym::getUID();
   const Symbol KEY_S = isym::getUID();
   const Symbol KEY_T = isym::getUID();
   const Symbol KEY_U = isym::getUID();
   const Symbol KEY_V = isym::getUID();
   const Symbol KEY_W = isym::getUID();
   const Symbol KEY_X = isym::getUID();
   const Symbol KEY_Y = isym::getUID();
   const Symbol KEY_Z = isym::getUID();
   const Symbol KEY_0 = isym::getUID();
   const Symbol KEY_1 = isym::getUID();
   const Symbol KEY_2 = isym::getUID();
   const Symbol KEY_3 = isym::getUID();
   const Symbol KEY_4 = isym::getUID();
   const Symbol KEY_5 = isym::getUID();
   const Symbol KEY_6 = isym::getUID();
   const Symbol KEY_7 = isym::getUID();
   const Symbol KEY_8 = isym::getUID();
   const Symbol KEY_9 = isym::getUID();
   const Symbol KEY_SHIFT = isym::getUID();
   const Symbol KEY_CTRL = isym::getUID();
   const Symbol KEY_ALT = isym::getUID();
   const Symbol KEY_SPACE = isym::getUID();
   const Symbol KEY_OPENBRACE = isym::getUID();
   const Symbol KEY_CLOSEBRACE = isym::getUID();
   const Symbol KEY_SEMICOLON = isym::getUID();
   const Symbol KEY_APOSTROPHE = isym::getUID();
   const Symbol KEY_COMMA = isym::getUID();
   const Symbol KEY_PERIOD = isym::getUID();
   const Symbol KEY_SLASH = isym::getUID();
   const Symbol KEY_BACKSLASH = isym::getUID();
   const Symbol KEY_ENTER = isym::getUID();
   const Symbol KEY_INSERT = isym::getUID();
   const Symbol KEY_DELETE = isym::getUID();
   const Symbol KEY_HOME = isym::getUID();
   const Symbol KEY_END = isym::getUID();
   const Symbol KEY_PAGE_UP = isym::getUID();
   const Symbol KEY_PAGE_DOWN = isym::getUID();
   const Symbol KEY_UP = isym::getUID();
   const Symbol KEY_RIGHT = isym::getUID();
   const Symbol KEY_DOWN = isym::getUID();
   const Symbol KEY_LEFT = isym::getUID();
   /** @} */
   /** @} */
}


#endif
