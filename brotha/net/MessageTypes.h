/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

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
      UpdatePlayerInfo ///< client sends to update its info
      //...
   }; // MessageType

} // namespace net


#endif // NET_MESSAGE_TYPES_H
