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
 * File:          $RCSfile: GameThread.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:06 $
 * Version:       $Revision: 1.13 $
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

#include "GameThread.h"


namespace server {
   GameThread::GameThread(net::NetMgr *netMgr) {
      m_netMgr = netMgr;

      m_brothaGame = new BrothaGame(netMgr);

      #define reg(a) m_messageHandlers[net::a] = new a##MessageHandler(m_brothaGame, netMgr)
      reg(Login);
      reg(JoinAs);
      reg(Resync);
      reg(UpdatePlayerInfo);
      #undef reg
   }

   GameThread::~GameThread() {
      delete m_brothaGame;
   }

   void GameThread::run() {
      while(PR_AtomicIncrement(&mKillMe)) {
         PR_Sleep(PR_INTERVAL_MIN);

         std::vector<std::pair<net::Message*, net::NetMgr::ConnID> > msgs;
         m_netMgr->readAll(msgs);

         typedef std::vector<std::pair<net::Message*, net::NetMgr::ConnID> >::iterator MsgIter;
         for(MsgIter iter=msgs.begin();iter!=msgs.end();iter++) {
            // pass the message to the appropriate message handler
            /// @todo probably should add some checks to make sure the handler actually exists
            net::Message* msg = (*iter).first;
            
            MessageHandlerIter mIter = m_messageHandlers.find((net::MessageType)msg->getType());
            if(mIter != m_messageHandlers.end()) {
               MessageHandler* msgHandler = mIter->second;
               msgHandler->handleMessage(msg, iter->second);
            } else {
               LOG<<"No appropriate message handler: MessageType:"<<msg->getType()<<ENDL;
            }
         }

         // now that we've handled all the messages, let's update the game
         m_brothaGame->update();

         PR_AtomicDecrement(&mKillMe);
      }
   }
} // namespace server
