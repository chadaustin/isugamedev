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
 * File:          $RCSfile: NetMgr.h,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.15 $
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
         for (ConnMapIter cIter = m_connections.begin();
              cIter != m_connections.end();
              ++cIter) {
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

         /// @todo static state bad!  this isn't threadsafe
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
         if (m_connections.count(dest)) {
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
