/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "thread/Thread.h"

class GameServer : public thread::Thread {
public:
   GameServer();
   virtual ~GameServer();

   virtual void run();
};

#endif