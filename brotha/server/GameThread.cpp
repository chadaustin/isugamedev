/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "GameThread.h"


namespace server {
   GameThread::GameThread(net::NetMgr *netMgr) {
      m_netMgr = netMgr;

      m_brothaGame = new BrothaGame(netMgr);

      #define reg(a) m_messageHandlers[net::a] = new a##MessageHandler(m_brothaGame, netMgr)
      reg(Login);
      reg(JoinAs);
      reg(Resync);
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
