/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_NET_MANAGER_H
#define NET_NET_MANAGER_H

#include "Socket.h"
#include "Message.h"
#include <vector>
#include <utility>

namespace net {
   /**
    * Facade for all interactions over the network. All needed threads are
    * created and managed internally as well as the serialization and
    * deserialization of the messages.
    */
   class NetMgr {
   public:
      /// The connection ID type.
      typedef int ConnID;

   public:
      NetMgr() {
      }

      ~NetMgr() {
      }

      /**
       * Creates the resources necessary to handle the connection using the
       * given socket.
       *
       * @param sock    the socket to manage
       *
       * @return  the ID for the created connection
       */
      ConnID handleSocket(Socket *socket) {
         return 0;
      }

      /**
       * Sends the given message over the connection with the given ID.
       *
       * @param msg     the message to send over the wire
       * @param dest    the destination connection ID
       */
      void send(Message *msg, ConnID dest) {
         /// @todo fill me
      }

      /**
       * Reads all messages that have been read since the last read and puts
       * them in the given vector.
       *
       * @param msgs    filled with the messages read
       */
      void readAll( std::vector< std::pair<Message*, ConnID> >& msgs ) {
         /// @todo fill me
      }
   };
}

#endif
