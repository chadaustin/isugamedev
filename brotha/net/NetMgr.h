/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_NET_MANAGER_H
#define NET_NET_MANAGER_H

#include "Socket.h"
#include "Connection.h"
#include "Message.h"
#include <vector>
#include <utility>
#include <map>

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
         /// @todo terminate each connection that has been opened
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
         // create a new connection and return the ID
         static ConnID uniqueID = 0;
         Connection *newConnection = new Connection(socket);
         m_connections[uniqueID] = newConnection;
         return uniqueID++;
      }

      /**
       * Sends the given message over the connection with the given ID.
       *
       * @param msg     the message to send over the wire
       * @param dest    the destination connection ID
       */
      void send(Message *msg, ConnID dest) {
         // simply pass the message to the approprate client
         m_connections[dest]->send(msg);
      }

      /**
       * Reads all messages that have been read since the last read and puts
       * them in the given vector.
       *
       * @param msgs    filled with the messages read
       */
      void readAll( std::vector< std::pair<Message*, ConnID> >& msgs ) {
         // for each connection
         typedef std::map<ConnID, Connection*>::iterator ConnIter;
         for(ConnIter cIter=m_connections.begin();cIter!=m_connections.end();cIter++) {
            // read all the messages
            std::vector<Message*> messages;
            ((Connection*)cIter->second)->read(messages);
            // and place each in the return
            typedef std::vector<Message*>::iterator MsgIter;
            for(MsgIter mIter=messages.begin();mIter!=messages.end();mIter++) {
               msgs.push_back(std::make_pair(*mIter, cIter->first));
            }
         }
      }
   private:
      std::map<ConnID, Connection*> m_connections; // maps IDs to Connections
   };
}

#endif
