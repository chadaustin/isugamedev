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
#include <memory> //auto_ptr

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

      /// The message list type
      typedef std::vector< std::pair< net::Message*, ConnID> > MsgList;
      typedef MsgList::iterator MsgListIter;

      /// The connection to ID map
      typedef std::map<ConnID, Connection*> ConnMap;
      typedef ConnMap::iterator             ConnMapIter;

   public:
      NetMgr() {
      }

      ~NetMgr() {
         for(ConnMapIter cIter=m_connections.begin();cIter!=m_connections.end();cIter++) {
            delete cIter->second;
         }
      }

      /**
       * Creates the resources necessary to handle the connection using the
       * given socket.
       *
       * @param sock    the socket to manage
       *
       * @return  the ID for the created connection
       */
      ConnID handleSocket(std::auto_ptr<Socket> socket) {
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
       *
       * @return true if the connection exists, false otherwise
       */
      bool send(Message* msg, ConnID dest) {
         // simply pass the message to the approprate client
         ConnMapIter iter = m_connections.find(dest);
         if ( iter != m_connections.end() ) {
            m_connections[dest]->send(msg);
            return true;
         } else {
            return false;
         }
      }

      /**
       * Reads all messages that have been read since the last read and puts
       * them in the given vector.
       *
       * @param msgs    filled with the messages read
       */
      void readAll( MsgList& msgs ) {
         // for each connection
         ConnMapIter cIter=m_connections.begin();
         while(cIter!=m_connections.end()) {
            // read all the messages
            std::vector<Message*> messages;
            // if their was a problem reading the message (the socket messed up)
            if(!((Connection*)cIter->second)->read(messages)) {
               // let's close the connection and remove it from our knowledge
               delete cIter->second;
               m_connections.erase(cIter);
               // go through all the connections again
               cIter = m_connections.begin();
            } else {
               // and place each in the return
               typedef std::vector<Message*>::iterator MsgIter;
               for(MsgIter mIter=messages.begin();mIter!=messages.end();mIter++) {
                  msgs.push_back(std::make_pair(*mIter, cIter->first));
               }
               // move to the next connection
               ++cIter;
            }
         }
      }

   private:
      ConnMap m_connections; // maps IDs to Connections
   };
}

#endif
