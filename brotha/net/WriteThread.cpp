/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "util/HWNDstream.h"

#include "WriteThread.h"
#include "SocketException.h"

namespace net {
   WriteThread::WriteThread(OutputStream *oStream, MessageQueue *writeQueue)
      : m_oStream(oStream), m_writeQueue(writeQueue)
   {
      start();
   }

   WriteThread::~WriteThread() {
   }

   void WriteThread::run() {
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
                  Message* msg = (*iter);
                  (*m_oStream) << msg->getType() << msg->getSize();
                  msg->serialize(*m_oStream);
                  LOG<<"Sent Msg: type=0x"<<(msg->getType())
                           <<", size="<<msg->getSize()<<ENDL;
               }
            } else { // if not, release CPU
               PR_Sleep(PR_INTERVAL_MIN);
            }

            PR_AtomicDecrement(&mKillMe);
         }
      } catch (SocketException &e) {
         LOG<<"Failed to serialize msg: "<<e.what()<<ENDL;
      }
   }
} // namespace net
