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
 * File:          $RCSfile: WriteThread.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.8 $
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
