/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INPUT_SYMBOL_H
#define MW_INPUT_SYMBOL_H

#include <SDL.h>
#include <string>

namespace mw
{
   bool isMouseSymbol(const std::string& symbol);
   Uint8 stringToSDLButton(const std::string& symbol);
   const std::string& SDLButtonToString(const Uint8& button);
   SDLKey stringToSDLKey(const std::string& name);
   const std::string& SDLKeyToString(const SDLKey& key);
}

#endif
