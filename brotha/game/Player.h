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
 * Date modified: $Date: 2002-04-29 02:13:43 $
 * Version:       $Revision: 1.17 $
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
#include "Car.h"

namespace game {
   class Player {
   public:
      /// UID manager for player objects.
      typedef UIDManager<Player,PRUint32,1> UIDMgr;

      /// The UID type for players.
      typedef UIDMgr::UID UID;
      
      /// The UID reserved for UNKNOWN players.
      static const UID UNKNOWN;

 	  /// List of cars player owns
	  typedef std::vector<Car*> CarList;

	  /// Iterator for Car list
      typedef CarList::iterator CarListItr;

   public:
      /**
       * Creates a new player with the default name "Player".
       */
      Player();

      /**
       * Creates a new player with the given name.
       */
      Player( const std::string& name );

      /**
       * Destroys this player.
       */
      virtual ~Player();

      /**
       * Gets the unique ID associated with this player.
       */
      const UID& getUID() const;

       /**
       * Gets the players velocity
       *
       * @return the velocity of the player
       */
      gmtl::Vec3f getVelocity();

      /**
       * Gets the players position
       *
       * @return the position of the player
       */
      gmtl::Vec3f getPosition();

      /**
       * Sets player position to given position
       */
      void setPosition(gmtl::Vec3f newPosition);

      /**
       * Sets player velocity to given velocity
       */
      void setVelocity(gmtl::Vec3f newVelocity);

      /**
       * Sets whether this player is braking.
       *
       * @param flag    true if this player is braking, false otherwise
       */
      void setBrake( PRFloat64 flag );

      /**
       * Tests if this player is braking.
       *
       * @return  true if the player is braking, false otherwise
       */
      PRFloat64 getBrake() const;

      /**
       * Sets whether this player is turning left.
       *
       * @param flag    true if this player is turning left, false otherwise
       */
      void setTurnAngle( PRFloat64 flag );

      /**
       * Tests if this player is turning left.
       *
       * @return  true if the player is turning left, false otherwise
       */
      PRFloat64 getTurnAngle() const;

	   /**
	    * Increments Kills Statistic
	    */
	   void addKill(){
	 	   mKills++;
	   }

	   /**
	    * Queries for owned cars
	    *
	    * @return a list of Cars the player owns
	    */
	   CarList getCars(){
		   return mCars;
	   }
     
      /**
       * Adds another car to the player's list
       */
      void addCar(Car* car);

      /**
       * Removes a car from the player's list
       */
      void removeCar(Car* car);

      Object* getObject();

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

   private:
      /// This players's UID
      UID mUID;

      /// This player's name
      std::string mName;

      /// This player's velocity
      gmtl::Vec3f mVelocity;

      /// This player's position
      gmtl::Vec3f mPosition;

      /// This player's health
      PRFloat64 mHealth;

      /// Number of Player kills
      double mKills;

	   /// List of owned cars
	   CarList mCars;

      /// True if the player is braking
      PRFloat64 mBrake;

      /// True if the player is turning left
      PRFloat64 mTurnAngle;


   public: // accessors wouldn't be worth the effor here
      /// whether or not player is doing something (not serialized, server side only)
      bool mIsBraking;
      bool mIsHandBraking;
      bool mIsTurningLeft;
      bool mIsTurningRight;

   };
}

#endif
