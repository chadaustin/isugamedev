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
 * File:          $RCSfile: SoundManager.cpp,v $
 * Date modified: $Date: 2002-04-27 05:04:12 $
 * Version:       $Revision: 1.1 $
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
#include <stdexcept>
#include "SoundManager.h"

namespace sound {

   SoundManager::SoundManager() {
      mContext = audiere::CreateContext(0);
      if (!mContext) {
         throw std::runtime_error("Error creating Audiere context");
      }

      mJukebox            = new Jukebox(mContext);
      mSoundEffectManager = new SoundEffectManager(mContext);
   }


   SoundManager::~SoundManager() {
      delete mJukebox;
      delete mSoundEffectManager;
      delete mContext;
   }


   Jukebox*
   SoundManager::getJukebox() {
      return mJukebox;
   }


   SoundEffectManager*
   SoundManager::getSoundEffectManager() {
      return mSoundEffectManager;
   }
}
