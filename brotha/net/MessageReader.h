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
