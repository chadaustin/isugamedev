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
 * File:          $RCSfile: Jukebox.h,v $
 * Date modified: $Date: 2003-05-23 05:57:44 $
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
#ifndef SOUND_JUKEBOX_H
#define SOUND_JUKEBOX_H

#include <vector>
#include <string>
#include "audiere.h"

namespace sound {

   /**
    * Describes a collection of music tracks that may be queued up so that they
    * are played in succession. You generally want to get your Jukebox instance
    * from and instance of the SoundManager class.
    *
    * \code
    *    SoundManager* sndMgr = new SoundManager();
    *    sndMgr->getJukebox()->addTrack("song1.ogg");
    *    sndMgr->getJukebox()->addTrack("whatever.wav");
    *    // ...
    *    sndMgr->getJukebox()->play();
    * \endcode
    *
    * @see SoundManager
    */
   class Jukebox {
   public:
      /**
       * The Jukebox uses a specified context to create audio streams.
       */
      Jukebox(audiere::AudioDevice* context);

      /**
       * Return current size of playlist.
       */
      int getTrackCount() const;

      /**
       * Return the filename at position index.
       */
      const std::string& getTrack(int index) const;

      /**
       * Append a sound filename to the end of the playlist.
       */
      void addTrack(const std::string& track);

      /**
       * Remove the track from the playlist if it exists.  Otherwise, do
       * nothing.
       */
      void removeTrack(const std::string& track);

      /**
       * Remove the track at position index from the playlist.
       */
      void removeTrack(int index);

      /**
       * Start playing tracks sequentially from the jukebox.
       */
      void play();

      /**
       * Tell Jukebox to stop playing sound.
       */
      void stop();

      /**
       * Updates the jukebox, moving to the next song if necessary.
       *
       * Call this once every frame or so.
       */
      void update();

   private:
      void tryOpenTrack();
      void nextTrack();

      audiere::AudioDevicePtr mContext;
      std::vector<std::string> mTracks;

      int mCurrentIndex;
      audiere::OutputStreamPtr mCurrentTrack;
      bool mIsPlaying;
   };
}

#endif
