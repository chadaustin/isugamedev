/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef BROTHA_SERVER_H
#define BROTHA_SERVER_H

#include "ListenServer.h"
#include "GameThread.h"
#include <vector>

namespace server {
   class BrothaServer {
   public:
      BrothaServer() {
         m_gameThread = 0;
         m_listenServer = 0;
      }

      ~BrothaServer() {
         StopServer();
         StopWebServer();
      }

      void StartServer() {
         m_netMgr = new net::NetMgr();

         m_gameThread   = new GameThread(m_netMgr);
         m_listenServer = new ListenServer(m_netMgr);

         m_gameThread->start();
         m_listenServer->start();
      }

      void StopServer() {
         if(m_gameThread != 0) {
            m_gameThread->stop();
         }
         if(m_listenServer != 0) {
            m_listenServer->stop();
         }

         delete m_netMgr;
         m_netMgr = 0;

         m_gameThread   = 0;
         m_listenServer = 0;
      }

      void StartWebServer() {
         // TODO: jcjcjcjc
      }

      void StopWebServer() {
         // TODO: jcjcjcjc
      }
   private:
      GameThread *m_gameThread;
      ListenServer *m_listenServer;

      net::NetMgr *m_netMgr;
   };
} // namespace server

#endif // BROTHA_SERVER_H
