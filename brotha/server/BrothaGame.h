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
 * File:          $RCSfile: BrothaGame.h,v $
 * Date modified: $Date: 2002-05-01 22:12:45 $
 * Version:       $Revision: 1.15 $
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
#include <set>
#include "game/GameTimer.h"
#include "game/GameLogic.h"
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

      ~BrothaGame();

      /**
       * Sends the message to everyone
       *
       * @param msg           the message to send
       * @param onlyInGame    whether or not to send to those only in the game
       * @pre  player != NULL
       */
      void sendToAll( net::Message* msg, bool onlyInGame );

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
      void addPlayer( game::Player* player, net::NetMgr::ConnID cID);

      /**
       * Removes the given player
       *
       * @param player     the player to remove
       */
      void removePlayer( game::Player* player );

      /**
       * Removes the given connection
       *
       * @param cID     the connection to remove
       */
      void removeConnection( net::NetMgr::ConnID cID );

      /**
       * Joins the player with said connection to the game.
       *
       * @param cID     the connection id
       * @pre  cID has already been added
       */
      void joinPlayer( net::NetMgr::ConnID cID );

      /**
       * Gets the player with the given UID.
       *
       * @param uid   the UID of the player to retrieve
       *
       * @return  the player if they exist, NULL if no playe has that UID
       */
      game::Player* getPlayer( game::Player::UID uid );

      /**
       * Gets the player with the given ConnID.
       *
       * @param cID   the ConnID of the player to retrieve
       *
       * @return  the player if they exist, NULL if no playe has that ConnID
       */
      game::Player* getPlayer( net::NetMgr::ConnID cID );

      /**
       * Gets the ConnID for the given player.
       *
       * @param player   the address of the player to retrieve
       *
       * @return  the ConnID if they exist, -1 otherwise
       */
      net::NetMgr::ConnID getConnectionID( game::Player* player );

      /**
       * Gets the ConnID for the given UID.
       *
       * @param uid   the UID of the ConnID to retrieve
       *
       * @return  the ConnID if they exist, -1 otherwise
       */
      net::NetMgr::ConnID getConnectionID( game::Player::UID uid );

      /**
       * Gets the UID for the given ConnID.
       *
       * @param cID   the ConnID of the UID to retrieve
       *
       * @return  the UID if they exist, -1 otherwise
       */
      game::Player::UID getUID( net::NetMgr::ConnID cID );

      /**
       * Gets the UID for the given player.
       *
       * @param player   the address of the player retrieve
       *
       * @return  the UID if they exist, -1 otherwise
       */
      game::Player::UID getUID( game::Player *player );

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

      /// Gets the game logic for this server.
      game::GameLogic& getLogic();

   private:

      /// The game timer.
      game::GameTimer mGameTime;

      /// All players that are in the game (actually UID->ConnID)
      typedef std::map<game::Player::UID, net::NetMgr::ConnID> PlayerMap;
      typedef PlayerMap::iterator PlayerMapIter;
      PlayerMap mPlayers;

      /// All players that are connected (not necessary in the game)
      /// actually (ConnID->Player)
      typedef std::map<net::NetMgr::ConnID, game::Player*> PlayerConnectionMap;
      typedef PlayerConnectionMap::iterator PlayerConnectionMapIter;
      PlayerConnectionMap mConnectedPlayers;

      /// connections that have apparently closed
      typedef std::set<net::NetMgr::ConnID> ClosedConnectionMap;
      typedef ClosedConnectionMap::iterator ClosedConnectionMapIter;
      ClosedConnectionMap mClosedConnections;

      /// The network manager
      net::NetMgr *m_netMgr;

      /// The game logic
      game::GameLogic mLogic;
   };
}

#endif
