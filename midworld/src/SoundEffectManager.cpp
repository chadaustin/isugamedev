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
 * Date modified: $Date: 2002-07-07 02:21:11 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "SoundEffectManager.h"

namespace mw
{
   SoundEffectManager::SoundEffectManager(audiere::Context* context)
   {
      mContext = context;
      mNextStream = 0;
      for (int i = 0; i < MAX_SOUNDS; ++i)
      {
         mStreams[i] = 0;
      }
   }

   SoundEffectManager::~SoundEffectManager()
   {
      for (int i = 0; i < MAX_SOUNDS; ++i)
      {
         delete mStreams[i];
      }
   }

   void
   SoundEffectManager::playSound(const std::string& sound)
   {
      delete mStreams[mNextStream];
      audiere::Stream* stream = mContext->openStream(sound.c_str());
      if (stream)
      {
         stream->play();
      }
      mStreams[mNextStream] = stream;

      mNextStream = (mNextStream + 1) % MAX_SOUNDS;
   }
}
