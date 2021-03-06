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
 * Date modified: $Date: 2002-05-03 07:24:49 $
 * Version:       $Revision: 1.28 $
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
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Object.h"

namespace game {
   class Player {
   public:
      /// UID manager for player objects.
      typedef util::UIDManager<Player,PRUint32,1> UIDMgr;

      /// The UID type for players.
      typedef UIDMgr::UID UID;
      
      /// The UID reserved for UNKNOWN players.
      static const UID UNKNOWN;

   public:
      /**
       * Creates a new player with the given name.
       */
      Player(const std::string& name = "Player");

      /**
       * Destroys this player.
       */
      virtual ~Player();

      /**
       * Gets the unique ID associated with this player.
       */
      const UID& getUID() const;

      /**
       * Gets the players health
       *
       * @return the health of the player
       */
      PRUint32 getHealth() const {
         return mHealth;
      }

      /**
       * Gets the players health
       *
       * @return the health of the player
       */
      PRUint32 getKills() const{
         return mKills;
      }

      /**
       * Gets the players number of coins
       *
       * @return the coins of the player
       */
      PRUint32 getCoins() const{
         return mCoins;
      }

      /**
       * Gets the players number of deaths
       *
       * @return the deaths of the player
       */
      PRUint32 getDeaths() const{
         return mDeaths;
      }

      /**
       * Sets the players health
       */
      void setHealth(PRUint32 health) {
         mHealth = health;
      }

      /**
       * Sets the players health
       */
      void setKills(PRUint32 kills) {
         mKills = kills;
      }

      /**
       * Sets the players health
       */
      void setCoins(PRUint32 coins){
         mCoins = coins;
      }

      /**
       * Sets the players number of deaths
       */
      void setDeaths(PRUint32 deaths){
         mDeaths = deaths;
      }

      /// Gets the UID of the vehicle object that this player drives.
      const Object::UID& getVehicle() const;

      /// Sets the object that is this player's vehicle.
      void setVehicle(const Object::UID& vehicle);

   public:
      /**
       * Gets the name of this player.
       *
       * @return  the name of the player
       */
      const std::string& getName() const;

      /**
       * Sets the name of this player to the given value.
       *
       * @param name    the new name for this player
       */
      void setName(const std::string& name);

      virtual PRUint32 getSize();
      virtual void serialize(net::OutputStream& os);
      virtual void deserialize(net::InputStream& os);

      virtual void clone(const Player* p) {
         mName = p->mName;
         mVelocity = p->mVelocity;
         mPosition = p->mPosition;
         mHealth = p->mHealth;
         mVehicle = p->mVehicle;
         mKills = p->mKills;
         mDeaths = p->mDeaths;
         mCoins = p->mCoins;
      }

   private:
      /// This players's UID
      UID mUID;

      /// This player's name
      std::string mName;

      /// This player's velocity
      gmtl::Vec3f mVelocity;

      /// This player's position
      gmtl::Vec3f mPosition;

      /// The UID of the object in the world that is this player's vehicle
      Object::UID mVehicle;

      /// This player's health
      PRUint32 mHealth;

      /// The number of kills this player has
      PRUint32 mKills;

      /// The number of deaths the player has
      PRUint32 mDeaths;

      /// The number of coins this player has
      PRUint32 mCoins;

   public: // accessors wouldn't be worth the effor here
      /// whether or not player is doing something (not serialized, server side only)
      bool mIsAccelerating;
      bool mIsBraking;
      bool mIsHandBraking;
      bool mIsTurningLeft;
      bool mIsTurningRight;
   };
}

#endif
