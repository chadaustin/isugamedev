/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef BROTHA_SERVER_H
#define BROTHA_SERVER_H

#include "net/MessageQueue.h"
#include "GameServer.h"
#include "ListenServer.h"
#include "WriteServer.h"
#include <vector>

namespace server {
   class BrothaServer {
   public:
      BrothaServer() {
         m_writeQueue = 0;
         m_readQueue = 0;

         m_clients = 0;

         m_gameServer = 0;
         m_listenServer = 0;
         m_writeServer = 0;
      }

      ~BrothaServer() {
         StopServer();
         StopWebServer();
      }

      void StartServer() {
         m_writeQueue = new net::MessageQueue();
         m_readQueue  = new net::MessageQueue();

         m_clients = new std::vector<Client>;

         m_gameServer   = new GameServer(m_writeQueue, m_readQueue);
         m_listenServer = new ListenServer(m_clients);
         m_writeServer  = new WriteServer(m_clients, m_writeQueue);

         m_gameServer->start();
         m_listenServer->start();
         m_writeServer->start();
      }

      void StopServer() {
         if(m_gameServer != 0) {
            m_gameServer->stop();
         }
         if(m_listenServer != 0) {
            m_listenServer->stop();
         }
         if(m_writeServer != 0) {
            m_writeServer->stop();
         }

         m_gameServer   = 0;
         m_listenServer = 0;
         m_writeServer  = 0;

         delete m_writeQueue;
         delete m_readQueue;
         m_writeQueue = 0;
         m_readQueue = 0;

         delete m_clients;
         m_clients = 0;
      }

      void StartWebServer() {
         // TODO: jcjcjcjc
      }

      void StopWebServer() {
         // TODO: jcjcjcjc
      }
   private:
      net::MessageQueue *m_writeQueue;
      net::MessageQueue *m_readQueue;
      std::vector<Client> *m_clients;

      GameServer *m_gameServer;
      ListenServer *m_listenServer;
      WriteServer *m_writeServer;
   };
} // namespace server

#endif // BROTHA_SERVER_H