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
 * File:          $RCSfile: MessageTypes.h,v $
 * Date modified: $Date: 2002-05-02 09:12:02 $
 * Version:       $Revision: 1.9 $
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

#ifndef NET_MESSAGE_TYPES_H
#define NET_MESSAGE_TYPES_H


namespace net {

   enum MessageType {
      Login, ///< client sends to login
      Disconnect, ///< client sends to disconnection from game
      OK, ///< generic response object
      JoinAs, ///< client sends to join game
      Enter, ///< server sends to place client in a location
      Resync, ///< client sends to request resyncing world
      AddObj, ///< seerver sends to add an object
      UpdateObj, ///< server sends to update an object
      DelObj, ///< server sends to delete an object
      AddPlayer, ///< server sends to add a player
      UpdatePlayer, ///< server sends to update a player object
      DelPlayer, ///< server sends to remove an object
      UpdatePlayerInfo, ///< client sends to update its info
      GarageData, ///< server sends data for the garage
      RequestGarageData, ///< client sends to request garage data
      ChangeLocation ///< client sends to request to switch between garage/game
      //...
   }; // MessageType

} // namespace net


#endif // NET_MESSAGE_TYPES_H
