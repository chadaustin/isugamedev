/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: SoundEffectManager.h,v $
 * Date modified: $Date: 2002-04-24 21:51:01 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
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
 ************************************************************ brotha-cpr-end */
#ifndef SOUND_SOUND_EFFECT_MANAGER_H
#define SOUND_SOUND_EFFECT_MANAGER_H

#include <string>
#include <audiere.h>

namespace sound {

   /**
    * Handles the triggering of sound effects for an application. Sounds played
    * through the SoundEffectManager are generally loaded into memory and played
    * from there rather than streaming from the disk.
    */
   class SoundEffectManager {
   public:
      /**
       * Creates a new SoundEffectManager for the given Audiere context.
       *
       * @param context    the Audiere context to use
       */
      SoundEffectManager(audiere::Context* context);

      /**
       * Destroys this manager and terminates all sounds currently being played
       * by this manager.
       */
      ~SoundEffectManager();

      /**
       * Plays the sound contained within the given file.
       *
       * @param sound      the filename in which the sound is stored
       */
      void playSound(const std::string& sound);

   private:
      enum { MAX_SOUNDS = 8 };
    
      audiere::Context* mContext;
      audiere::Stream* mStreams[MAX_SOUNDS];
      int mNextStream;
   };
}

#endif
