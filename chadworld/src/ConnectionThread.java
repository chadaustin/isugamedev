package chadworld;

import java.io.*;
import java.net.*;


class ConnectionThread extends Thread {
  private Socket m_socket;
  private Server m_server;

  private static int s_connection = 1;

  ConnectionThread(Socket socket, Server server) {
    m_socket = socket;
    m_server = server;
  }

  private static int getConnection() {
    return s_connection++;
  }

  public void run() {

    m_server.m_connection_list.add(this);

    int connection = getConnection();
    System.out.println("Client " + connection + " connected...");

    Entity ent = null;

    try {
      ObjectOutputStream os =
        new ObjectOutputStream(m_socket.getOutputStream());
      ObjectInputStream  is =
        new ObjectInputStream (m_socket.getInputStream());

      // get the user's login
      LoginPacket lp = (LoginPacket)is.readObject();

      // acknowledge
      ent = m_server.m_entities.getEntity(lp.username);
      os.writeObject(new ResponsePacket(ent.id));

      // send the world to the user
      os.writeObject(new WorldPacket(m_server.m_world));

      while (true) {
        // read a packet
        Packet p = (Packet)is.readObject();

        if (p instanceof InputPacket) {

          InputPacket ip = (InputPacket)p;
          System.out.println("Key event!");
	  m_server.m_world_thread.processInputEvent(ent, ip);

        } else if (p instanceof TalkPacket) {

	  TalkPacket tp = (TalkPacket)p;
	  System.out.println("Got a talk packet!");
	  m_server.m_world_thread.processTalkEvent(ent, tp);

        } else {
	  // unknown packet
	}
      }
    }
    catch (Exception e) {
      System.out.println(e);
    }

    try {
      m_socket.close();
    }
    catch (Exception e) {
    }

    m_server.m_connection_list.remove(this);

    m_server.m_entities.remove(ent);

    System.out.println("Closed connection with client " + connection);
  }
}
