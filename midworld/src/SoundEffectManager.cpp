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
 * Date modified: $Date: 2002-10-01 00:37:13 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include "SoundEffectManager.h"

// XXX: Remove these functions when audiere 1.9.1 is released (which
// coincidentally contains these functions).
namespace audiere
{
  typedef char u8;

  inline OutputStream* OpenSound(
    AudioDevice* device,
    SampleBuffer* buffer)
  {
    return OpenSound(device, buffer->openStream(), false);
  }

  inline SampleBuffer* CreateSampleBuffer(SampleSource* source)
  {
    // If the stream is not seekable, we can't create a buffer for it.
    if (!source || !source->isSeekable()) {
      return 0;
    }

    int stream_length = source->getLength();
    int channel_count, sample_rate;
    SampleFormat sample_format;
    source->getFormat(channel_count, sample_rate, sample_format);

    int stream_length_bytes =
      stream_length * channel_count * GetSampleSize(sample_format);
    u8* buffer = new u8[stream_length_bytes];
    source->setPosition(0);  // in case the source has been read from already
    source->read(stream_length, buffer);

    SampleBuffer* sb =  CreateSampleBuffer(
       buffer, stream_length, channel_count,
       sample_rate, sample_format);
    delete[] buffer;
    return sb;
  }

  inline SampleBuffer* CreateSampleBuffer(const char* filename)
  {
    return CreateSampleBuffer(OpenSampleSource(filename));
  }
} // namespace audiere

namespace mw
{
   SoundEffectManager::SoundEffectManager(audiere::AudioDevice* device)
   {
      mDevice = device;
      mNextStream = 0;
   }

   void
   SoundEffectManager::playSound(const std::string& sound)
   {
      audiere::SampleBuffer* buffer = getBuffer(sound);
      if (buffer)
      {
         audiere::OutputStream* stream = audiere::OpenSound(mDevice.get(),
                                                            buffer);
         if (stream)
         {
            stream->play();
            mStreams[mNextStream] = stream;
            mNextStream = (mNextStream + 1) % MAX_SOUNDS;
         }
      }
   }

   bool
   SoundEffectManager::preload(const std::string& sound)
   {
      return (getBuffer(sound) != 0);
   }

   void
   SoundEffectManager::emptyCache()
   {
      mCache.clear();
   }

   audiere::SampleBuffer*
   SoundEffectManager::getBuffer(const std::string& sound)
   {
      // Check the cache first
      BufferMap::iterator itr = mCache.find(sound);

      // Cache hit. Return a new stream for the cached buffer
      if (itr != mCache.end())
      {
         return itr->second.get();
      }
      // Cache miss. Open the sound into a buffer and cache it
      else
      {
         std::cout<<"SoundEffectManager: Cache miss for '"<<sound<<"'"<<std::endl;
         audiere::RefPtr<audiere::SampleBuffer> buffer =
                        audiere::CreateSampleBuffer(sound.c_str());
         if (buffer)
         {
            mCache[sound] = buffer;
            return buffer.get();
         }
         return 0;
      }
   }
}
