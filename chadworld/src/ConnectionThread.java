package chadworld;

import java.io.*;
import java.net.*;


class ConnectionThread extends Thread {
  private Socket m_socket;
  private World m_world;
  private EntityDatabase m_db;

  private static int s_connection = 1;

  ConnectionThread(Socket s, World world, EntityDatabase db) {
    m_socket = s;
    m_world  = world;
    m_db     = db;
  }

  private static int getConnection() {
    return s_connection++;
  }

  public void run() {

    int connection = getConnection();
    System.out.println("Client " + connection + " connected...");

    try {
      ObjectOutputStream os =
        new ObjectOutputStream(m_socket.getOutputStream());
      ObjectInputStream  is =
        new ObjectInputStream (m_socket.getInputStream());

      LoginPacket lp = (LoginPacket)is.readObject();

      Entity e = m_db.createEntity(lp.username);
      m_db.add(e);
      os.writeObject(new ResponsePacket(e.id));

      os.writeObject(new WorldPacket(m_world));
      
      m_socket.close();
    }
    catch (Exception e) {
      System.out.println(e);
    }

    System.out.println("Closed connection with client " + connection);
  }
}
