/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "ReadThread.h"
#include "SocketException.h"

namespace net {
   ReadThread::ReadThread(InputStream *in, MessageQueue *readQueue)
      : m_msgReader(in)
   {
      m_readQueue = readQueue;

      start();
   }

   ReadThread::~ReadThread() {
   }

   void ReadThread::run() {
      try {
         while(PR_AtomicIncrement(&mKillMe)) {
            m_readQueue->push(m_msgReader.readMessage());
            PR_AtomicDecrement(&mKillMe);
         }
      } catch (SocketException &e) {
         std::cout<<"Failed to deserialize msg: "<<e.what()<<std::endl;
      }
   }

   unsigned int Message::mNumMsgsInMemory = 0;
} // namespace net
