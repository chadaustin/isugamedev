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
 * File:          $RCSfile: GameLogic.h,v $
 * Date modified: $Date: 2002-05-03 07:18:34 $
 * Version:       $Revision: 1.20 $
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
#ifndef GAME_GAME_LOGIC_H
#define GAME_GAME_LOGIC_H

#include <map>
#include <vector>
#include "Player.h"
#include "GameTimer.h"
#include "xml/BrothaData.h"

namespace game
{
   /**
    * Contains the current state information relative to the game as well as all
    * the data required to display the game.
    */
   class GameLogic
   {
   public:
     GameLogic();
     ~GameLogic();

     void update(float time);

      /**
       * Adds the given player to the game.
       *
       * @param player     the player to add
       * @pre  player != NULL
       */
     void add(Player* player);
        
     /**
      * Removes a player from the current game
      * 
      * @param player      the player to remove
      */
     void remove(Player* player);

	  /**
	   * Adds a given object in the game
	   *
	   * @param object     the object to add
	   * @pre object != NULL
	   */
	  void add(game::Object* object);

     /**
      * Removes the given object
      *
      * @param object     the object to remove
      */
	  void remove(game::Object* object);

     /// Gets the list of players in the game.
     std::vector<Player*>& getPlayers();

     /// Gets the list of objects in the game.
     std::vector<Object*>& getObjects();

     /**
      * Gets the player with the given name.
      *
      * @param name     the name of the player to search for
      *
      * @return   the player if found; NULL otherwise
      */
     Player* getPlayer(const std::string& name);

     /**
      * Gets the object with the given UID.
      */
     Object* getObject(const Object::UID& uid);

     /**
      * outputs list of players.. for debugging
      */
     void outputList();

     /**
      * Updates the xml stats for update
      */
     void updateStats();

     /**
      * Gets the stats from data and loads them in for the player
      */
     void getStats(Player* player);

   private:
     /**
      * Processes the inputs on the given player.
      */
     void processInput(Player* player, float dt);

   private:
      //vector for players in the game.
      typedef std::vector<Player*> PlayerList;
      PlayerList mPlayer;
      typedef PlayerList::iterator PlayerListItr;

      typedef std::vector<Object*> ObjectList;
      ObjectList mObject;
      typedef ObjectList::iterator ObjectListItr;
   };
}

#endif
