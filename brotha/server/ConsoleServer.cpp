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
      println("help, quit              - exit server");
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
