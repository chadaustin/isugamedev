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
 * Date modified: $Date: 2002-05-01 18:42:30 $
 * Version:       $Revision: 1.12 $
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
#include <vector>
#include "Player.h"
#include "GameTimer.h"

namespace game
{
   /**
    * Contains the current state information relative to the game as well as all
    * the data required to display the game.
    */
   class BrothaGame
   {
   public:
     BrothaGame();
     ~BrothaGame();

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

     /**
      * Gets the player with the given name.
      *
      * @param name     the name of the player to search for
      *
      * @return   the player if found; NULL otherwise
      */
     Player* getPlayer(const std::string& name);

     void outputList();

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
