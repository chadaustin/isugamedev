/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef BROTHA_SERVER_H
#define BROTHA_SERVER_H

#include "ListenServer.h"
#include "GameThread.h"
#include "WebServer.h"
#include <vector>

namespace server {
   class BrothaServer {
   public:
      BrothaServer() {
         m_gameThread = 0;
         m_listenServer = 0;
         m_webServer = 0;
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
            delete m_gameThread;
         }
         if(m_listenServer != 0) {
            m_listenServer->stop();
            delete m_listenServer;
         }

         delete m_netMgr;
         m_netMgr = 0;

         m_gameThread   = 0;
         m_listenServer = 0;
      }

      void StartWebServer() {
         m_webServer = new WebServer();

         m_webServer->start();
      }

      void StopWebServer() {
         if(m_webServer != 0) {
            m_webServer->stop();
         }

         m_webServer = 0;
      }
   private:
      GameThread *m_gameThread;
      ListenServer *m_listenServer;
      WebServer *m_webServer;

      net::NetMgr *m_netMgr;
   };
} // namespace server

#endif // BROTHA_SERVER_H
