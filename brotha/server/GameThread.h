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
 * File:          $RCSfile: GameThread.h,v $
 * Date modified: $Date: 2002-04-28 16:41:06 $
 * Version:       $Revision: 1.10 $
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

#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include "thread/Thread.h"
#include "net/NetMgr.h"
#include "net/MessageTypes.h"
#include "BrothaGame.h"
#include "LoginMessageHandler.h"
#include "JoinAsMessageHandler.h"
#include "ResyncMessageHandler.h"
#include "UpdatePlayerInfoMessageHandler.h"
#include "MessageHandler.h"

namespace server {
   class GameThread : public thread::Thread {
   public:
      GameThread(net::NetMgr *netMgr);
      virtual ~GameThread();

      virtual void run();
   private:
      net::NetMgr* m_netMgr;
      BrothaGame* m_brothaGame;

      typedef std::map<net::MessageType, MessageHandler*> MessageHandlers;
      typedef MessageHandlers::iterator MessageHandlerIter;
      MessageHandlers m_messageHandlers;
   };
} // namespace server

#endif // GAME_SERVER_H
