/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include "Socket.h"
#include "Message.h"
#include <vector>
#include <utility>

namespace net {
   class NetMgr {
   public:
      NetMgr() {
      }

      ~NetMgr() {
      }

      int handleSocket(Socket *socket) {
         return 0;
      }

      void send(Message *msg, int destination) {
      }

      std::vector<std::pair<Message*, int> > readAll() {
         std::vector<std::pair<Message*, int> > retVal;

         // TODO

         return retVal;
      }
   };
}

#endif