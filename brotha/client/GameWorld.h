/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
 * File:          $RCSfile: GameWorld.h,v $
 * Date modified: $Date: 2002-05-03 07:18:33 $
 * Version:       $Revision: 1.2 $
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
#ifndef CLIENT_GAMEWORLD_H
#define CLIENT_GAMEWORLD_H

#include "game/Object.h"
#include "game/Player.h"

namespace client {
   /**
    * Container for the client-side cache of all objects and players in the
    * game.
    */
   class GameWorld
   {
   public:
      typedef std::vector<game::Object*> ObjectList;
      typedef std::vector<game::Player*> PlayerList;

   public:
      GameWorld();
      ~GameWorld();

      /// @post World takes ownership of the obj ptr.
      void addObject(game::Object* obj);
      void removeObject(const game::Object::UID& uid);
      game::Object* getObject(const game::Object::UID& uid);

      /// @post World takes ownership of the player ptr.
      void addPlayer(game::Player* player);
      void removePlayer(const game::Player::UID& player);
      game::Player* getPlayer(const game::Player::UID& uid);

      /**
       * Updates the object in the world with the data in the given object.
       */
      void update(const game::Object* obj);

      /**
       * Updates the player in the world with the data in the given player.
       */
      void update(const game::Player* player);

   private:
      ObjectList mObjs;
      PlayerList mPlayers;
   };
}

#endif
