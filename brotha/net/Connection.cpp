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
 * File:          $RCSfile: Connection.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.7 $
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
#include "Connection.h"

namespace net {
   Connection::Connection(std::auto_ptr<Socket> socket) {
      m_socket = socket;

      m_readQueue = new MessageQueue();
      m_writeQueue = new MessageQueue();

      m_readThread = new ReadThread(m_socket->getInputStream(), m_readQueue);
      m_writeThread = new WriteThread(m_socket->getOutputStream(), m_writeQueue);
   }

   Connection::~Connection() {
      m_readThread->stop();
      m_writeThread->stop();

      delete m_readQueue;
      delete m_writeQueue;

      delete m_readThread;
      delete m_writeThread;
   }

   void Connection::send(Message *message) {
      m_writeQueue->push(message);
   }

   bool Connection::read(std::vector<Message*> &messages) {
      // if the thread is still running, read the messages
      if(m_readThread->isRunning()) {
         m_readQueue->read(messages);
         return true;
      } else { // if not
         return false;
      }
   }
}
