/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "WriteThread.h"

namespace net {
   WriteThread::WriteThread(Socket *socket, MessageQueue *writeQueue) {
      m_socket = socket;
      m_writeQueue = writeQueue;

      start();
   }

   WriteThread::~WriteThread() {
   }

   void WriteThread::run() {
      OutputStream *oStream = m_socket->getOutputStream();
      try {
         while(PR_AtomicIncrement(&mKillMe)) {
            // read all messages
            std::vector<Message*> messages;
            m_writeQueue->read(messages);

            // if we have some
            if(!messages.empty()) {
               // write each
               typedef std::vector<Message*>::iterator MsgIter;
               for(MsgIter iter=messages.begin();iter!=messages.end();iter++) {
                  (*oStream) << (*iter)->getType() << (*iter)->getSize();
                  (*iter)->serialize(*oStream);
               }
            } else { // if not, release CPU
               PR_Sleep(PR_INTERVAL_MIN);
            }

            PR_AtomicDecrement(&mKillMe);
         }
      } catch (SocketException &e) { }
   }
} // namespace net
