/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_MESSAGE_READER_H
#define NET_MESSAGE_READER_H


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
#include <iostream>

namespace net {

   class MessageReader {
   public:
      MessageReader(InputStream* input_stream) {
         mInputStream = input_stream;
      }

      Message* readMessage() {
         PRUint32 tag, size;
         (*mInputStream) >> tag >> size;

         std::cout<<"New message: type=0x"<<std::hex<<std::hex<<tag<<std::dec
                  <<", size="<<size<<std::endl;

         // make sure we read everything (in case of bad message)
         PRUint8* buffer = new PRUint8[size];
         mInputStream->read(buffer, size);

         Message* msg;
         switch (tag) {
            case MSG_LOGIN:
               msg = new LoginMessage();
               break;

            case MSG_DISCONNECT:
               msg = new DisconnectMessage();
               break;

            case MSG_OK:
               msg = new OKMessage();
               break;

            case MSG_JOIN_AS:
               msg = new JoinAsMessage();
               break;

            case MSG_ENTER:
               msg = new EnterMessage();
               break;

            case MSG_RESYNC:
               msg = new ResyncMessage();
               break;

            case MSG_ADD_OBJ:
               msg = new AddObjMessage();
               break;

            case MSG_UPDATE_OBJ:
               msg = new UpdateObjMessage();
               break;

            case MSG_DEL_OBJ:
               msg = new DelObjMessage();
               break;

            case MSG_ADD_PLAYER:
               msg = new AddPlayerMessage();
               break;

            case MSG_UPDATE_PLAYER:
               msg = new UpdatePlayerMessage();
               break;

            case MSG_DEL_PLAYER:
               msg = new DelPlayerMessage();
               break;

            case MSG_UPDATE_PLAYER_INFO:
               msg = new UpdatePlayerInfoMessage();
               break;

            default:
               std::cout<<"ERROR: unknown message type"<<std::endl;
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
