/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

class MessageHandler {
public:
   MessageHandler() {}
   ~MessageHandler() {}

   virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) = 0;
};

#endif // MESSAGE_HANDLER_H
