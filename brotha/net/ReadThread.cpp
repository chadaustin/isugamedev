/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "ReadThread.h"

namespace net {
   ReadThread::ReadThread(Socket *socket, MessageQueue *readQueue) {
      m_socket = socket;
      m_readQueue = readQueue;

      start();
   }

   ReadThread::~ReadThread() {
   }

   void ReadThread::run() {
      MessageReader msgReader(m_socket->getInputStream());
      while(PR_AtomicIncrement(&mKillMe)) {
         m_readQueue->push(msgReader.readMessage());

         PR_AtomicDecrement(&mKillMe);
      }
   }
} // namespace net
