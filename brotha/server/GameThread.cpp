/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "GameThread.h"


namespace server {
   GameThread::GameThread(net::NetMgr *netMgr) {
      m_netMgr = netMgr;

      m_brothaGame = new game::BrothaGame();

      #define reg(a) m_messageHandlers[net::a] = new a##MessageHandler(m_brothaGame, netMgr)
      reg(Login);
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
            MessageHandler *msgHandler = m_messageHandlers[(net::MessageType)msg->getType()];
            msgHandler->handleMessage(msg, (*iter).second);
         }

         PR_AtomicDecrement(&mKillMe);
      }
   }
} // namespace server
