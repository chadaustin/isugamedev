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
 * File:          $RCSfile: SoundEffectManager.h,v $
 * Date modified: $Date: 2003-01-02 03:32:55 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_SOUND_EFFECT_MANAGER_H
#define SIREN_SOUND_EFFECT_MANAGER_H

#include <string>
#include <map>
#include <audiere.h>

namespace siren
{
   /**
    * Handles the triggering of sound effects for an application. Sounds played
    * through the SoundEffectManager are generally loaded into memory and played
    * from there rather than streaming from the disk.
    */
   class SoundEffectManager
   {
   public:
      /**
       * Creates a new SoundEffectManager for the given Audiere context.
       *
       * @param context    the Audiere context to use
       */
      SoundEffectManager(audiere::AudioDevice* device);

      /**
       * Plays the sound contained within the given file.
       *
       * @param sound      the filename in which the sound is stored
       */
      void playSound(const std::string& sound);

      /**
       * Preloads the sound contained within the given file and stores it in the
       * cache for later use.
       *
       * @param sound      the filename in which the sound is stored
       *
       * @return  true if the sound was loaded successfully, false otherwise
       */
      bool preload(const std::string& sound);

      /**
       * Removes all sounds contained in the cache.
       */
      void emptyCache();

   private:
      /**
       * Checks the cache for an effect associated with the given string. If a
       * buffer for the sound is not in the cache, it is created. Otherwise, the
       * buffer in the cache is returned.
       *
       * @param sound      the name of the sound to get
       *
       * @return  a buffer for the sound, throws an exception if it could not be opened
       */
      audiere::SoundEffect* getEffect(const std::string& sound);

   private:
      audiere::AudioDevicePtr mDevice;

      typedef std::map<std::string, audiere::SoundEffectPtr> EffectMap;
      EffectMap mCache;
   };
}

#endif
