/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: SoundEffectManager.cpp,v $
 * Date modified: $Date: 2002-11-15 14:25:49 $
 * Version:       $Revision: 1.10 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include "SoundEffectManager.h"


namespace mw
{
   SoundEffectManager::SoundEffectManager(audiere::AudioDevice* device)
   {
      mDevice = device;
   }

   void
   SoundEffectManager::playSound(const std::string& sound)
   {
      getEffect(sound)->play();
   }

   bool
   SoundEffectManager::preload(const std::string& sound)
   {
      return (getEffect(sound) != 0);
   }

   void
   SoundEffectManager::emptyCache()
   {
      mCache.clear();
   }

   audiere::SoundEffect*
   SoundEffectManager::getEffect(const std::string& sound)
   {
      // Check the cache first
      EffectMap::iterator itr = mCache.find(sound);

      // Cache hit. Return a new stream for the cached buffer
      if (itr != mCache.end())
      {
         return itr->second.get();
      }
      // Cache miss. Open the sound into a buffer and cache it
      else
      {
         std::cout << "SoundEffectManager: Cache miss for '"
                   << sound << "'" << std::endl;
         audiere::SoundEffectPtr effect = audiere::OpenSoundEffect(
            mDevice.get(),
            sound.c_str(),
            audiere::SINGLE);
         if (!effect)
         {
            throw std::runtime_error("Could not load sound: " + sound);
         }
         
         mCache[sound] = effect;
         return effect.get();
      }
   }
}
