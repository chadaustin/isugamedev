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
 * File:          $RCSfile: SoundManager.cpp,v $
 * Date modified: $Date: 2003-01-02 04:18:18 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <stdexcept>
#include "SoundManager.h"

namespace siren
{
   SoundManager::SoundManager()
   {
      adr::AudioDevicePtr device(adr::OpenDevice());
      if (!device)
      {
         device = adr::OpenDevice("null");
         if (!device)
         {
            throw std::runtime_error("Error opening Audiere device");
         }
      }

      mJukebox            = new Jukebox(device.get());
      mSoundEffectManager = new SoundEffectManager(device.get());
   }

   SoundManager::~SoundManager()
   {
      delete mJukebox;
      delete mSoundEffectManager;
   }

   Jukebox*
   SoundManager::getJukebox()
   {
      return mJukebox;
   }

   SoundEffectManager*
   SoundManager::getSoundEffectManager()
   {
      return mSoundEffectManager;
   }
}
