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
 * File:          $RCSfile: SoundEffectManager.h,v $
 * Date modified: $Date: 2002-09-08 03:04:51 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_SOUND_EFFECT_MANAGER_H
#define MW_SOUND_EFFECT_MANAGER_H

#include <string>
#include <audiere.h>

namespace mw
{
   namespace adr = audiere;

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
      SoundEffectManager(adr::AudioDevice* device);

      /**
       * Plays the sound contained within the given file.
       *
       * @param sound      the filename in which the sound is stored
       */
      void playSound(const std::string& sound);

   private:
      enum { MAX_SOUNDS = 8 };

      adr::RefPtr<adr::AudioDevice> mDevice;
      adr::RefPtr<adr::OutputStream> mStreams[MAX_SOUNDS];
      int mNextStream;
   };
}

#endif
