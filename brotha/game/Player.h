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
 * Date modified: $Date: 2002-03-29 14:46:01 $
 * Version:       $Revision: 1.6 $
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
#include "Object.h"

namespace game
{
   class Player : public Object {
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
      ~Player();

      /**
       * Sets whether this player is accelerating.
       *
       * @param flag    true if this player is accelerating, false otherwise
       */
      void setAccelerate( bool flag );

      /**
       * Tests if this player is accelerating.
       *
       * @return  true if the player is accelerating, false otherwise
       */
      bool isAccelerating() const;

      /**
       * Sets whether this player is braking.
       *
       * @param flag    true if this player is braking, false otherwise
       */
      void setBrake( bool flag );

      /**
       * Tests if this player is braking.
       *
       * @return  true if the player is braking, false otherwise
       */
      bool isBraking() const;

      /**
       * Sets whether this player is turning left.
       *
       * @param flag    true if this player is turning left, false otherwise
       */
      void setTurnLeft( bool flag );

      /**
       * Tests if this player is turning left.
       *
       * @return  true if the player is turning left, false otherwise
       */
      bool isTurningLeft() const;

      /**
       * Sets whether this player is turning right.
       *
       * @param flag    true if this player is turning right, false otherwise
       */
      void setTurnRight( bool flag );

      /**
       * Tests if this player is turning right.
       *
       * @return  true if the player is turning right, false otherwise
       */
      bool isTurningRight() const;

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
      void setName( const std::string& name );

      virtual PRUint32 getType() const;
      virtual PRUint32 getSize();
      virtual void serialize(net::OutputStream& os);
      virtual void deserialize(net::InputStream& os);

   private:
      /// This player's name
      std::string mName;

      /// True if the player is accelerating
      bool mAccelerate;

      /// True if the player is braking
      bool mBrake;

      /// True if the player is turning left
      bool mTurnLeft;

      /// True if the player is turning right
      bool mTurnRight;
   };
}

#endif
