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
 * File:          $RCSfile: LevelLoader.h,v $
 * Date modified: $Date: 2002-11-04 07:37:17 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_LEVEL_LOADER_H
#define MW_LEVEL_LOADER_H

#include <string>
#include "Entity.h"

namespace mw
{
   class GameState;

   /**
    * Instances of this object know how to read and parse the Midworld level
    * files and setup the game accordingly.
    */
   class LevelLoader
   {
   public:
      /**
       * Loads in the level contained in the given file and modifies the given
       * game state accordingly.
       *
       * @param level         the filename containg the level to load
       * @param gameState     the game state to modify
       *
       * @throws  std::runtime_error if there was a problem reading the file
       */
      static void load(const std::string& level, GameState* gameState);
      
   private:
      LevelLoader();
      LevelLoader(const LevelLoader&);
      void operator=(const LevelLoader&);
   };
}

#endif
