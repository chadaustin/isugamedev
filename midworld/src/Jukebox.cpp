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

   int
   Jukebox::getTrackCount() const
   {
      return mTracks.size();
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
      for (int i = 0; i < getTrackCount(); ++i)
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
