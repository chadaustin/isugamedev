/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
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
 * File:          $RCSfile: PySDLUtil.cpp,v $
 * Date modified: $Date: 2003-02-14 09:06:46 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <boost/python.hpp>
#include <siren/siren.h>

using namespace boost::python;
using namespace siren;

void exportSDLUtil()
{
   def("WarpMouse", SDL_WarpMouse);

#define EV(x)  .value(#x, SDLK_ ## x)
   enum_<SDLKey>("Key")
      EV(UNKNOWN)
      EV(FIRST)
      EV(BACKSPACE)
      EV(TAB)
      EV(CLEAR)
      EV(RETURN)
      EV(PAUSE)
      EV(ESCAPE)
      EV(SPACE)
      EV(EXCLAIM)
      EV(QUOTEDBL)
      EV(HASH)
      EV(DOLLAR)
      EV(AMPERSAND)
      EV(QUOTE)
      EV(LEFTPAREN)
      EV(RIGHTPAREN)
      EV(ASTERISK)
      EV(PLUS)
      EV(COMMA)
      EV(MINUS)
      EV(PERIOD)
      EV(SLASH)
      EV(0)
      EV(1)
      EV(2)
      EV(3)
      EV(4)
      EV(5)
      EV(6)
      EV(7)
      EV(8)
      EV(9)
      EV(COLON)
      EV(SEMICOLON)
      EV(LESS)
      EV(EQUALS)
      EV(GREATER)
      EV(QUESTION)
      EV(AT)
      EV(LEFTBRACKET)
      EV(BACKSLASH)
      EV(RIGHTBRACKET)
      EV(CARET)
      EV(UNDERSCORE)
      EV(BACKQUOTE)
      EV(a)
      EV(b)
      EV(c)
      EV(d)
      EV(e)
      EV(f)
      EV(g)
      EV(h)
      EV(i)
      EV(j)
      EV(k)
      EV(l)
      EV(m)
      EV(n)
      EV(o)
      EV(p)
      EV(q)
      EV(r)
      EV(s)
      EV(t)
      EV(u)
      EV(v)
      EV(w)
      EV(x)
      EV(y)
      EV(z)
      EV(DELETE)
      EV(WORLD_0)
      EV(WORLD_1)
      EV(WORLD_2)
      EV(WORLD_3)
      EV(WORLD_4)
      EV(WORLD_5)
      EV(WORLD_6)
      EV(WORLD_7)
      EV(WORLD_8)
      EV(WORLD_9)
      EV(WORLD_10)
      EV(WORLD_11)
      EV(WORLD_12)
      EV(WORLD_13)
      EV(WORLD_14)
      EV(WORLD_15)
      EV(WORLD_16)
      EV(WORLD_17)
      EV(WORLD_18)
      EV(WORLD_19)
      EV(WORLD_20)
      EV(WORLD_21)
      EV(WORLD_22)
      EV(WORLD_23)
      EV(WORLD_24)
      EV(WORLD_25)
      EV(WORLD_26)
      EV(WORLD_27)
      EV(WORLD_28)
      EV(WORLD_29)
      EV(WORLD_30)
      EV(WORLD_31)
      EV(WORLD_32)
      EV(WORLD_33)
      EV(WORLD_34)
      EV(WORLD_35)
      EV(WORLD_36)
      EV(WORLD_37)
      EV(WORLD_38)
      EV(WORLD_39)
      EV(WORLD_40)
      EV(WORLD_41)
      EV(WORLD_42)
      EV(WORLD_43)
      EV(WORLD_44)
      EV(WORLD_45)
      EV(WORLD_46)
      EV(WORLD_47)
      EV(WORLD_48)
      EV(WORLD_49)
      EV(WORLD_50)
      EV(WORLD_51)
      EV(WORLD_52)
      EV(WORLD_53)
      EV(WORLD_54)
      EV(WORLD_55)
      EV(WORLD_56)
      EV(WORLD_57)
      EV(WORLD_58)
      EV(WORLD_59)
      EV(WORLD_60)
      EV(WORLD_61)
      EV(WORLD_62)
      EV(WORLD_63)
      EV(WORLD_64)
      EV(WORLD_65)
      EV(WORLD_66)
      EV(WORLD_67)
      EV(WORLD_68)
      EV(WORLD_69)
      EV(WORLD_70)
      EV(WORLD_71)
      EV(WORLD_72)
      EV(WORLD_73)
      EV(WORLD_74)
      EV(WORLD_75)
      EV(WORLD_76)
      EV(WORLD_77)
      EV(WORLD_78)
      EV(WORLD_79)
      EV(WORLD_80)
      EV(WORLD_81)
      EV(WORLD_82)
      EV(WORLD_83)
      EV(WORLD_84)
      EV(WORLD_85)
      EV(WORLD_86)
      EV(WORLD_87)
      EV(WORLD_88)
      EV(WORLD_89)
      EV(WORLD_90)
      EV(WORLD_91)
      EV(WORLD_92)
      EV(WORLD_93)
      EV(WORLD_94)
      EV(WORLD_95)
      EV(KP0)
      EV(KP1)
      EV(KP2)
      EV(KP3)
      EV(KP4)
      EV(KP5)
      EV(KP6)
      EV(KP7)
      EV(KP8)
      EV(KP9)
      EV(KP_PERIOD)
      EV(KP_DIVIDE)
      EV(KP_MULTIPLY)
      EV(KP_MINUS)
      EV(KP_PLUS)
      EV(KP_ENTER)
      EV(KP_EQUALS)
      EV(UP)
      EV(DOWN)
      EV(RIGHT)
      EV(LEFT)
      EV(INSERT)
      EV(HOME)
      EV(END)
      EV(PAGEUP)
      EV(PAGEDOWN)
      EV(F1)
      EV(F2)
      EV(F3)
      EV(F4)
      EV(F5)
      EV(F6)
      EV(F7)
      EV(F8)
      EV(F9)
      EV(F10)
      EV(F11)
      EV(F12)
      EV(F13)
      EV(F14)
      EV(F15)
      EV(NUMLOCK)
      EV(CAPSLOCK)
      EV(SCROLLOCK)
      EV(RSHIFT)
      EV(LSHIFT)
      EV(RCTRL)
      EV(LCTRL)
      EV(RALT)
      EV(LALT)
      EV(RMETA)
      EV(LMETA)
      EV(LSUPER)
      EV(RSUPER)
      EV(MODE)
      EV(COMPOSE)
      EV(HELP)
      EV(PRINT)
      EV(SYSREQ)
      EV(BREAK)
      EV(MENU)
      EV(POWER)
      EV(EURO)
      EV(UNDO)
      EV(LAST)
   ;
#undef EV
}
