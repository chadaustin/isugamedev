#include <iostream>
#include <string>
#include "BrothaServer.h"


server::BrothaServer g_BrothaServer;


inline void println(const std::string& s) {
   std::cout << s << std::endl;
}


int main(int argc, char** argv) {

   std::cout << "Console Warn-a-Brotha Server" << std::endl;
   while (true) {
      std::string cmd;
      std::cout << "brotha> " << std::flush;
      std::getline(std::cin, cmd);
      if (!cin) {
         std::cout << std::endl;
         break;
      }

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
         break;
      } else if (cmd == "help") {
         println("help                    - get help");
         println("startserver, start      - start brothaserva");
         println("stopserver, stop        - start brothaserva");
         println("startwebserver, startws - start brothaserva");
         println("stopwebserver, stopws   - start brothaserva");
      } else {
         println("Unknown command: " + cmd);
      }
   }

}
