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
 * File:          $RCSfile: BrothaServer.h,v $
 * Date modified: $Date: 2002-04-28 16:41:06 $
 * Version:       $Revision: 1.9 $
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
         LOG<<"Started server"<<ENDL;
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
