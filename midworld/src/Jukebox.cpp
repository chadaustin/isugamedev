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
 * File:          $RCSfile: Jukebox.cpp,v $
 * Date modified: $Date: 2002-07-07 02:21:11 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "Jukebox.h"

namespace mw
{
   Jukebox::Jukebox(audiere::Context* context)
   {
      mContext = context;
      mCurrentTrack = 0;
      mIsPlaying = false;
   }

   Jukebox::~Jukebox()
   {
      delete mCurrentTrack;
   }

   unsigned int
   Jukebox::getTrackCount() const
   {
      return (unsigned int)mTracks.size();
   }

   const std::string&
   Jukebox::getTrack(int i) const
   {
      // ASSERT (i >= 0 && i < mTracks.size())
      return mTracks[i];
   }

   void
   Jukebox::addTrack(const std::string& track)
   {
      mTracks.push_back(track);
   }

   void
   Jukebox::removeTrack(const std::string& track)
   {
      for (unsigned int i = 0; i < getTrackCount(); ++i)
      {
         if (track == getTrack(i))
         {
            removeTrack(i);
            return;
         }
      }
   }

   void
   Jukebox::removeTrack(int index)
   {
      // ASSERT (i >= 0 && i < mTracks.size())
      mTracks.erase(mTracks.begin() + index);
   }

   void
   Jukebox::play()
   {
      if (mIsPlaying || getTrackCount() == 0)
      {
         return;
      }

      tryOpenTrack();
      mIsPlaying = true;
   }

   void
   Jukebox::stop()
   {
      /// @todo make this stop() better...  it has really stupid logic
      delete mCurrentTrack;
      mCurrentTrack = 0;
      mCurrentIndex = 0;
      mIsPlaying = false;
   }

   void
   Jukebox::update()
   {
      if (!mIsPlaying)
      {
         return;
      }

      if (mCurrentTrack)
      {
         if (!mCurrentTrack->isPlaying())
         {
            nextTrack();
         }
      }
      else
      {
         if (getTrackCount() >= 0)
         {
            mCurrentIndex = 0;
            tryOpenTrack();
         }
      }
   }

   void
   Jukebox::tryOpenTrack()
   {
      // validate index
      mCurrentIndex = mCurrentIndex % getTrackCount();

      delete mCurrentTrack;
      mCurrentTrack = mContext->openStream(mTracks[mCurrentIndex].c_str());
      if (mCurrentTrack)
      {
         mCurrentTrack->play();
      }
   }

   void
   Jukebox::nextTrack()
   {
      if (getTrackCount() >= 0)
      {
         mCurrentIndex = (mCurrentIndex + 1) % getTrackCount();

         delete mCurrentTrack;
         mCurrentTrack = mContext->openStream(mTracks[mCurrentIndex].c_str());
      }
      else
      {
         delete mCurrentTrack;
         mCurrentTrack = 0;
      }
   }
}
