package chadworld;

import chadworld.*;
import java.io.*;
import java.net.*;
import javax.vecmath.*;


/**
 * The server application. It keeps a synchronized copy of the world
 * and dynamic entity data.  It also listens for client connections,
 * sending proper packets
 */
public class Server {

  World m_world = new World();
  EntityDatabase m_entities = new EntityDatabase();
  ConnectionList m_connection_list = new ConnectionList();
  WorldThread m_world_thread;

  /**
   * Cycle in an infinite loop, collecting connections and spawning
   * threads!
   */
  void run(int port) {

    System.out.println("Starting server on port " + port + "...");

    m_world_thread = new WorldThread(m_connection_list, m_entities);
    m_world_thread.start();

    try {
      ServerSocket s = new ServerSocket(port);
      while (true) {
        new ConnectionThread(s.accept(), this).start();
      }
    }
    catch (Exception e) {
      System.out.println(e);
    }
  }

  public static void main(String[] args) {

    // see if the user specified a port number
    int port = Configuration.port;
    if (args.length == 1) {
      port = Integer.parseInt(args[0]);
    } else if (args.length >= 2) {
      System.out.println("Usage: java chadworld.Server [optional-port]");
    }

    new Server().run(port);
  }
}
