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
 * File:          $RCSfile: BrothaGame.h,v $
 * Date modified: $Date: 2002-03-29 15:35:11 $
 * Version:       $Revision: 1.4 $
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
#ifndef BROTHAGAME_H
#define BROTHAGAME_H

#include <map>
#include "game/GameTimer.h"
#include "game/Player.h"
#include "net/NetMgr.h"

namespace server {
   /**
    * Contains the current state information relative to the game as well as all
    * the data required to display the game.
    */
   class BrothaGame {
   public:
      /**
       * Creates a new game with no players.
       */
      BrothaGame(net::NetMgr *netMgr);

      /**
       * Updates the state of all objects in the game.
       */
      void update();

      /**
       * Adds the given player to players that have connection pool.
       *
       * @param player     the player to add
       * @param cID        the connection id
       * @pre  player != NULL
       */
      void add( game::Player* player, net::NetMgr::ConnID cID);

      /**
       * Joins the player with said connection to the game.
       *
       * @param cID     the connection id
       * @pre  cID has already been added
       */
      void joinPlayer( net::NetMgr::ConnID cID );

      /**
       * Performs a resync on the player referred to by the connection.
       *
       * @param cID     the connection id
       * @pre  cID refers to a player already in the game
       */
      void resync( net::NetMgr::ConnID cID );

      /**
       * Pauses or unpauses the game.
       *
       * @param pause   true to pause the game, false to unpause the game
       */
      void setPaused( bool pause );

      /**
       * Tests if the game is paused.
       *
       * @return  true if the game is paused, false otherwise
       */
      bool isPaused() const;

      /**
       * Gets the game timer
       */
      const game::GameTimer& getGameTimer() const;

   private:
      typedef std::map<game::Player::UID, game::Player*> PlayerMap;
      typedef std::map<net::NetMgr::ConnID, game::Player*> PlayerConnectionMap;

      /// The game timer.
      game::GameTimer mGameTime;

      /// All players that have actually joined the game.
      PlayerMap mPlayers;

      /// All players that have may a connection
      PlayerConnectionMap mConnectedPlayers;

      /// The network manager
      net::NetMgr *m_netMgr;
   };
}

#endif
