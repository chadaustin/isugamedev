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


namespace net {

   class MessageReader {
   public:
      MessageReader(InputStream* input_stream) {
         mInputStream = input_stream;
      }

      Message* readMessage() {
         PRUint32 tag, size;
         (*mInputStream) >> tag >> size;

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

            default:
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
