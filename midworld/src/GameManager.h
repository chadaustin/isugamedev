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
 * File:          $RCSfile: GameManager.h,v $
 * Date modified: $Date: 2002-11-25 12:39:13 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_GAME_MANAGER_H
#define MW_GAME_MANAGER_H

#include "SoundManager.h"

namespace mw
{
   /**
    * This singleton object manages references to the sound, model, texture,
    * and resource managers.
    *
    * @see SoundManager
    */
   class GameManager
   {
   private:
      /// This class is a singleton; use instance() instead.
      GameManager();

      /// Not implemented so that copy will cause a compile-time error.
      GameManager(const GameManager& copy);

      /// Destroys this manager.
      ~GameManager();

   public:
      /// Gets the singleton instance of this class.
      static GameManager& instance();

      /// Gets the sound manager.
      SoundManager* getSoundManager() const;

   private:
      static void destroyGameManager();

      /// Music and sound effects manager.
      SoundManager* mSoundMgr;

      /// The singleton instance of this class.
      static GameManager* mInstance;
   };
}

#endif
