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
 * File:          $RCSfile: GameLogic.h,v $
 * Date modified: $Date: 2002-03-27 00:51:33 $
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
#ifndef BROTHAGAME_H
#define BROTHAGAME_H

#include <map>
#include "game/GameTimer.h"
#include "game/Player.h"

/**
 * Contains the current state information relative to the game as well as all
 * the data required to display the game.
 */
class BrothaGame
{
public:
   /**
    * Creates a new game with no players.
    */
   BrothaGame();

   /**
    * Updates the state of all objects in the game.
    */
   void update();

   /**
    * Adds the given player to the game.
    *
    * @param player     the player to add
    * @pre  player != NULL
    */
   void add( Player* player);

   /**
    * Sets which player is on the local machine. If player is NULL, then it is
    * assumed that there is no local player and this is a dedicated server.
    *
    * @param player     the player corresponding to the local player
    */
   void setLocalPlayer( Player* player );

   /**
    * Gets the player on the local machine. If there is no local player, as
    * could be the case on a dedicated server, this method will return NULL.
    *
    * @return  the local player or NULL if there is no player on the local
    *          machine
    */
   Player* getLocalPlayer();

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
   const GameTimer& getGameTimer() const;

private:
   typedef std::map<Player::UID, Player*> PlayerMap;

   /// The game timer.
   GameTimer mGameTime;

   /// All players in the game.
   PlayerMap mPlayers;

   /// The local player.
   Player* mLocalPlayer;
};

#endif
