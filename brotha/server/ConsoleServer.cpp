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
 * File:          $RCSfile: ConsoleServer.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:06 $
 * Version:       $Revision: 1.6 $
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
#include <iostream>
#include <string>
#include <stdlib.h>
#include "BrothaServer.h"


server::BrothaServer g_BrothaServer;


inline void println(const std::string& s) {
   std::cout << s << std::endl;
}

bool processcmd(const std::string& cmd) {
   if (cmd == "startserver" || cmd == "start") {
      println("Starting game server");
      g_BrothaServer.StartServer();
   } else if (cmd == "stopserver" || cmd == "stop") {
      println("Stopping game server");
      g_BrothaServer.StopServer();
   } else if (cmd == "startwebserver" || cmd == "startws") {
      println("Starting web server");
      g_BrothaServer.StartWebServer();
   } else if (cmd == "stopwebserver" || cmd == "stopws") {
      println("Stopping web server");
      g_BrothaServer.StopWebServer();
   } else if (cmd == "exit" || cmd == "quit") {
      return false;
   } else if (cmd == "help") {
      println("");
      println("help                    - get help");
      println("startserver, start      - start brothaserva");
      println("stopserver, stop        - stop brothaserva");
      println("startwebserver, startws - start webserva");
      println("stopwebserver, stopws   - stop webserva");
      println("exit, quit              - exit server");
      println("");
      println("You may also pass commands as arguments to the program.");
      println("");
   } else {
      println("Unknown command: " + cmd);
   }
   return true;
}


int main(int argc, char** argv) {

   for (int i = 1; i < argc; ++i) {
      if (!processcmd(argv[i])) {
         return EXIT_FAILURE;
      }
   }

   std::cout << "Console Warn-a-Brotha Server" << std::endl;
   while (true) {
      std::string cmd;
      std::cout << "brotha> " << std::flush;
      std::getline(std::cin, cmd);
      if (!std::cin) {
         std::cout << std::endl;
         break;
      }

      if (!processcmd(cmd)) {
         break;
      }
   }

}
