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
 * File:          $RCSfile: MessageReader.h,v $
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

#ifndef NET_MESSAGE_READER_H
#define NET_MESSAGE_READER_H


#include "util/HWNDstream.h"

#include "InputStream.h"
#include "MessageTypes.h"

#include "ByteBuffer.h"
#include "DisconnectMessage.h"
#include "LoginMessage.h"
#include "OKMessage.h"
#include "JoinAsMessage.h"
#include "EnterMessage.h"
#include "ResyncMessage.h"
#include "AddObjMessage.h"
#include "UpdateObjMessage.h"
#include "DelObjMessage.h"
#include "AddPlayerMessage.h"
#include "UpdatePlayerMessage.h"
#include "DelPlayerMessage.h"
#include "UpdatePlayerInfoMessage.h"

namespace net {

   class MessageReader {
   public:
      MessageReader(InputStream* input_stream) {
         mInputStream = input_stream;
      }

      Message* readMessage() {
         PRUint32 tag, size;
         (*mInputStream) >> tag >> size;

         LOG<<"New message: type=0x"<<std::hex<<std::hex<<tag<<std::dec
                  <<", size="<<size<<ENDL;

         // make sure we read everything (in case of bad message)
         PRUint8* buffer = new PRUint8[size];
         mInputStream->read(buffer, size);

         Message* msg;
         switch (tag) {
            case Login:
               msg = new LoginMessage();
               break;

            case Disconnect:
               msg = new DisconnectMessage();
               break;

            case OK:
               msg = new OKMessage();
               break;

            case JoinAs:
               msg = new JoinAsMessage();
               break;

            case Enter:
               msg = new EnterMessage();
               break;

            case Resync:
               msg = new ResyncMessage();
               break;

            case AddObj:
               msg = new AddObjMessage();
               break;

            case UpdateObj:
               msg = new UpdateObjMessage();
               break;

            case DelObj:
               msg = new DelObjMessage();
               break;

            case AddPlayer:
               msg = new AddPlayerMessage();
               break;

            case UpdatePlayer:
               msg = new UpdatePlayerMessage();
               break;

            case DelPlayer:
               msg = new DelPlayerMessage();
               break;

            case UpdatePlayerInfo:
               msg = new UpdatePlayerInfoMessage();
               break;

            default:
               LOG<<"ERROR: unknown message type"<<ENDL;
               delete[] buffer;
               return 0;
         }

         // stick the packet data in a byte buffer to restrict the
         // message from reading farther than it should in the network
         // stream
         ByteBuffer bb;
         bb.write(buffer, size);
         delete[] buffer;

         // deserialize!
         msg->deserialize(bb);
         return msg;
      }

   private:
      InputStream* mInputStream;
   };
}


#endif
