/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_MESSAGE_TYPES_H
#define NET_MESSAGE_TYPES_H


namespace net {

   enum MessageType {
      MSG_LOGIN, ///< client sends to login
      MSG_DISCONNECT, ///< client sends to disconnection from game
      MSG_OK, ///< generic response object
      MSG_JOIN_AS, ///< client sends to join game
      MSG_ENTER, ///< server sends to place client in a location
      MSG_RESYNC, ///< client sends to request resyncing world
      MSG_ADD_OBJ, ///< seerver sends to add an object
      MSG_UPDATE_OBJ, ///< server sends to update an object
      MSG_DEL_OBJ, ///< server sends to delete an object
      MSG_ADD_PLAYER, ///< server sends to add a player
      MSG_UPDATE_PLAYER, ///< server sends to update a player object
      MSG_DEL_PLAYER, ///< server sends to remove an object
      MSG_UPDATE_PLAYER_INFO ///< client sends to update its info
      //...
   }; // MessageType

} // namespace net


#endif // NET_MESSAGE_TYPES_H
