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
 * File:          $RCSfile: Jukebox.h,v $
 * Date modified: $Date: 2002-10-11 04:47:56 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_JUKEBOX_H 
#define MW_JUKEBOX_H

#include <vector>
#include <string>
#include <audiere.h>

namespace mw
{
   namespace adr = audiere;

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
   class Jukebox
   {
   public:
      /**
       * The Jukebox uses a specified context to create audio streams.
       */
      Jukebox(adr::AudioDevice* device);

      /**
       * Return current size of playlist.
       */
      unsigned int getTrackCount() const;

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
       * Removes all tracks from the jukebox. This has the side effect of
       * stopping the currently playing song.
       */
      void clear();

      /**
       * Start playing tracks sequentially from the jukebox.
       */
      void play();

      /**
       * Tell Jukebox to stop playing sound.
       */
      void stop();

      /**
       * Moves to the next track in the playlist.
       */
      void next();

      /**
       * Moves to the previous track in the playlist.
       */
      void prev();

      /**
       * Determines if this jukebox is currently playing sound.
       */
      bool isPlaying() const;

      /**
       * Updates the jukebox, moving to the next song if necessary.
       *
       * Call this once every frame or so.
       */
      void update();

   private:
      void tryOpenTrack();

      adr::RefPtr<adr::AudioDevice> mDevice;
      std::vector<std::string> mTracks;

      int mCurrentIndex;
      adr::RefPtr<adr::OutputStream> mCurrentTrack;
      bool mIsPlaying;
   };
}

#endif
