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
 * File:          $RCSfile: GameWorld.cpp,v $
 * Date modified: $Date: 2002-05-03 02:41:48 $
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
#include "GameWorld.h"

namespace client {
   GameWorld::GameWorld() {}

   GameWorld::~GameWorld() {
      for (ObjectList::iterator itr=mObjs.begin(); itr!=mObjs.end(); ++itr) {
         delete *itr;
      }
      mObjs.clear();
      for (PlayerList::iterator itr=mPlayers.begin(); itr!=mPlayers.end(); ++itr) {
         delete *itr;
      }
      mPlayers.clear();
   }

   void GameWorld::addObject(game::Object* obj) {
      if (! getObject(obj->getUID())) {
         mObjs.push_back(obj);
      } else {
         std::cout<<"Object with UID "<<obj->getUID()<<" already in the world"<<std::endl;
      }
   }

   void GameWorld::removeObject(const game::Object::UID& uid) {
      // This is still OK if getObject() returns NULL
      delete getObject(uid);
   }

   game::Object* GameWorld::getObject(const game::Object::UID& uid) {
      for (ObjectList::iterator itr=mObjs.begin(); itr!=mObjs.end(); ++itr) {
         if ((*itr)->getUID() == uid) {
            return *itr;
         }
      }
      return NULL;
   }

   void GameWorld::addPlayer(game::Player* player) {
      if (! getPlayer(player->getUID())) {
         mPlayers.push_back(player);
      } else {
         std::cout<<"Player with UID "<<player->getUID()<<" already in the world"<<std::endl;
      }
   }

   void GameWorld::removePlayer(const game::Player::UID& uid) {
      // This is still OK if getPlayer() returns NULL
      delete getPlayer(uid);
   }

   game::Player* GameWorld::getPlayer(const game::Player::UID& uid) {
      for (PlayerList::iterator itr=mPlayers.begin(); itr!=mPlayers.end(); ++itr) {
         if ((*itr)->getUID() == uid) {
            return *itr;
         }
      }
      return NULL;
   }
}
