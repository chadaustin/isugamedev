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
 * File:          $RCSfile: BrothaGame.cpp,v $
 * Date modified: $Date: 2002-04-22 02:26:18 $
 * Version:       $Revision: 1.3 $
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
#include "BrothaGame.h"
#include <algorithm>

namespace game
{
   void BrothaGame::update(){
      
   }

   void BrothaGame::addPlayer(Player* player){
      assert (player != NULL && "Cannot add a NULL player!");

      std::cout << "About to add player!" << std::endl;
      mPlayer.push_back(player);
      std::cout << "Player added." << std::endl;
   }

   void BrothaGame::removePlayer(Player* player){
      PlayerListItr Itr;
      Itr = std::find(mPlayer.begin(),mPlayer.end(),player);
      if (Itr != mPlayer.end()){
         mPlayer.erase(Itr);
      }
   }

   void BrothaGame::addObject(Object* object){
      assert ( object != NULL && "Cannot add a Null object!" );
      mObject.push_back(object);
   }

   void BrothaGame::removeObject(Object* object){
      ObjectListItr Itr;
      Itr = std::find(mObject.begin(), mObject.end(), object);
      if(Itr != mObject.end()){
         mObject.erase(Itr);
      }
   }
   
   void BrothaGame::outputList(){
      for (int i=0; i < mPlayer.size(); i++){
         std::cout << mPlayer[i]->getName() << std::endl;
      }
   }

}
