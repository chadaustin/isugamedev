package chadworld;

import java.io.*;
import java.net.*;
import javax.vecmath.*;


class ConnectionThread extends Thread {
  private Socket m_socket;
  private Server m_server;

  private PacketInputStream  m_is;
  private PacketOutputStream m_os;

  private static int s_connection = 1;

  ConnectionThread(Socket socket, Server server) {
    m_socket = socket;
    m_server = server;
  }

  private static int getConnection() {
    return s_connection++;
  }

  public void run() {

    int connection = getConnection();
    System.out.println("Client " + connection + " connected...");

    Entity ent = null;

    try {
      m_os = new PacketOutputStream(m_socket.getOutputStream());
      m_is = new PacketInputStream (m_socket.getInputStream());

      // get the user's login
      LoginPacket lp = (LoginPacket)m_is.readPacket();

      // acknowledge
      ent = m_server.m_entities.getEntity(lp.username);
      m_os.writePacket(new ResponsePacket(ent.id));

      // send the world to the user
      m_os.writePacket(new WorldPacket(m_server.m_world));

      // begin sending world updates to this client
      m_server.m_connection_list.add(this);

      while (true) {
        // read a packet
        Packet p = (Packet)m_is.readPacket();

        if (p instanceof InputPacket) {

          InputPacket ip = (InputPacket)p;
	  m_server.m_world_thread.processInputEvent(ent, ip);

        } else if (p instanceof TalkPacket) {

	  TalkPacket tp = (TalkPacket)p;
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

  public void sendPacket(Packet p) {
    try {
      m_os.writePacket(p);
    }
    catch (Exception e) {
      System.out.println("Error writing packet");
      System.out.println(e);
    }
  }
}
