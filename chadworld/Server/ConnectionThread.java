package chadworld.server;
import chadworld.*;

import java.io.*;
import java.net.*;


class ConnectionThread extends Thread {
  Socket m_socket;

  static int s_connection = 1;

  ConnectionThread(Socket s) {
    m_socket = s;
  }

  public void run() {

    int connection = s_connection++;
    System.out.println("Client " + connection + " connected...");

    try {
      ObjectOutputStream os = new ObjectOutputStream(m_socket.getOutputStream());
      ObjectInputStream  is = new ObjectInputStream (m_socket.getInputStream());

      Packet p = (Packet)is.readObject();
      System.out.println(p.m_packet);
      
      m_socket.close();
    }
    catch (Exception e) {
      System.out.println(e);
    }

    System.out.println("Closed connection with client " + connection);
  }
}
