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
 * File:          $RCSfile: InputSymbol.h,v $
 * Date modified: $Date: 2003-02-22 23:53:34 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_INPUT_SYMBOL_H
#define SIREN_INPUT_SYMBOL_H

#include <SDL.h>
#include <string>
#include <siren/Export.h>

namespace siren
{
   SIREN_EXPORT(bool)               isMouseSymbol(const std::string& symbol);
   SIREN_EXPORT(Uint8)              stringToSDLButton(const std::string& symbol);
   SIREN_EXPORT(const std::string&) SDLButtonToString(const Uint8& button);
   SIREN_EXPORT(SDLKey)             stringToSDLKey(const std::string& name);
   SIREN_EXPORT(const std::string&) SDLKeyToString(const SDLKey& key);
}

#endif
