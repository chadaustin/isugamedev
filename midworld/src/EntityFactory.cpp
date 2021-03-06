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
 * File:          $RCSfile: EntityFactory.cpp,v $
 * Date modified: $Date: 2002-10-28 07:41:20 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include "EntityFactory.h"

namespace mw
{
   EntityFactory* EntityFactory::mInstance = 0;

   void
   EntityFactory::setGameState(GameState* gameState)
   {
      mGameState = gameState;
   }

   EntityFactory&
   EntityFactory::instance()
   {
      if (! mInstance)
      {
         mInstance = new EntityFactory();
      }

      return *mInstance;
   }

   EntityFactory::EntityFactory()
      : mGameState(0)
   {}

   EntityFactory::~EntityFactory()
   {}
}
