package chadworld.server;
import chadworld.*;

import java.io.*;
import java.net.*;


class ConnectionThread extends Thread {
  private Socket m_socket;
  private WorldPacket m_world;

  private static int s_connection = 1;

  ConnectionThread(Socket s, WorldPacket world) {
    m_socket = s;
    m_world = world;
  }

  public void run() {

    int connection = s_connection++;
    System.out.println("Client " + connection + " connected...");

    try {
      ObjectOutputStream os = new ObjectOutputStream(m_socket.getOutputStream());
      ObjectInputStream  is = new ObjectInputStream (m_socket.getInputStream());

      os.writeObject(m_world);
      
      m_socket.close();
    }
    catch (Exception e) {
      System.out.println(e);
    }

    System.out.println("Closed connection with client " + connection);
  }
}
