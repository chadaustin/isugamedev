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
 * File:          $RCSfile: SoundManager.h,v $
 * Date modified: $Date: 2003-02-22 23:53:35 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#ifndef SIREN_SOUND_MANAGER_H
#define SIREN_SOUND_MANAGER_H

#include "Jukebox.h"
#include "SoundEffectManager.h"

namespace siren
{
   /**
    * The SoundManager is a facade for creating and manipulating music and sound
    * effects in an application using Audiere as the backend. The SoundManager
    * has a Jukebox for queueing up and playing music tracks and a
    * SoundEffectManager for triggering non-music related sound effects.
    *
    * <h3>Example: Using the SoundManager</h3>
    * \code
    *    // Create a new sound manager
    *    SoundManager* mgr = new SoundManager();
    *
    *    // Queue up and play some music
    *    mgr->getJukebox()->addTrack("music/track1.ogg");
    *    mgr->getJukebox()->addtrack("music/track2.wav");
    *    mgr->getJukebox()->play();
    *
    *    // Trigger some sound effects
    *    mgr->getSoundEffectManager()->play("sfx/bullet_blast.wav");
    *    // ...
    *
    *    // Don't forget to free memory when we're done!
    *    delete mgr;
    * \endcode
    *
    * @see Jukebox
    * @see SoundEffectManager
    */
   class SIREN_CLASS SoundManager
   {
   public:
      /**
       * Creates a new SoundManager and initializes the Audiere context.
       *
       * @throw std::runtime_error     if there was a failure initializing
       *                               Audiere.
       */
      SoundManager();

      /**
       * Terminates all playing audio and releases memory used by the audio
       * subsystem.
       */
      ~SoundManager();

      /**
       * Gets the jukebox for this manager. The jukebox is responsible for the
       * queueing and playing of music tracks. Audio played by the Jukebox is
       * usually streamed from the disk.
       *
       * @return  this manager's Jukebox
       */
      Jukebox* getJukebox();

      /**
       * Gets the sound effect manager which is responsible for triggering sound
       * effects. Audio played by the SoundEffectManager is usually loaded into
       * memory and played from there.
       *
       * @return  this manager's SoundEffectManager
       */
      SoundEffectManager* getSoundEffectManager();

   private:
      Jukebox*            mJukebox;
      SoundEffectManager* mSoundEffectManager;
   };
}

#endif
