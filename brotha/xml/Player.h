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
 * File:          $RCSfile: Player.h,v $
 * Date modified: $Date: 2002-05-01 07:55:33 $
 * Version:       $Revision: 1.13 $
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
#ifndef DATA_PLAYER_H
#define DATA_PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "Stat.h"

namespace data {

   class Player {
   public:
      /// Creates a new player with the given name/pass pair.
      Player(const std::string& name, const std::string& password)
         : mName(name), mPassword(password)
      {}

      /// Gets this player's password.
      const std::string& getPassword() const {
         return mPassword;
      }

      /// Sets the password for this player.
      void setPassword(const std::string& password) {
         mPassword = password;
      }

      /// Gets the name of this player.
      const std::string& getName() const {
         return mName;
      }

      /// Gets the list of cars owned by this player.
      CarList& getCars() {
         return mCars;
      }

      /// Gets the list of stats for this player.
      StatList& getStats() {
         return mStats;
      }

      /// Adds the given car to this player's list of owned cars.
      void addCar(Car* c) {
         mCars.push_back(c);
      }

      /// Adds the given stat to this player's list of stats.
      void addStat(Stat* s) {
         mStats.push_back(s);
      }

      /**
       * Gets the stat with the given name from this player.
       *
       * @pre The player has a stat with the given name.
       */
      const std::string& getStat(const std::string& name) {
         StatList::iterator itr;
         for (itr = mStats.begin(); itr != mStats.end(); ++itr) {
            Stat* stat = *itr;
            if (stat->getName() == name) {
               return stat->getVal();
            }
         }
         assert(false && "Player does not have the stat requested");
      }

      /// Sets the stat with the given name to the given value.
      void setStat(const std::string& name, const std::string& value) {
         bool exists = false;
         StatList::iterator itr;
         for (itr = mStats.begin(); itr != mStats.end(); ++itr) {
            Stat* s = *itr;
            if (s->getName() == value) {
               s->setVal(value);
               exists = true;
            }
         }

         // add the stat since it does not already exist
         if (! exists) {
            mStats.push_back(new Stat(name, value));
         }
      }

      void xMLify(std::ostream& out) {
         out << "    <player name=\"" << mName << "\" password=\"" << mPassword << "\">" << std::endl;
         for (unsigned int i = 0; i < mCars.size(); ++i) {
            mCars[i]->xMLify(out);
         }
         for (unsigned int i = 0; i < mStats.size(); ++i) {
            mStats[i]->xMLify(out);
         }
         out << "   </player>" << std::endl;
      }
  
   private:
      /// The name of this player.
      std::string mName;

      /// The password for this player.
      std::string mPassword;

      /// The cars this player owns.
      CarList mCars;

      /// The stats for this player.
      StatList mStats;
   };

   typedef std::vector<Player*> PlayerList;
}

#endif
