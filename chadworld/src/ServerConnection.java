package chadworld;

import java.io.*;
import java.net.*;


class ServerConnection {
  private Socket m_socket;
  private OutputStream m_output_stream;
  private InputStream m_input_stream;
  private ObjectOutputStream m_object_output_stream;
  private ObjectInputStream m_object_input_stream;

  ServerConnection(String server) throws IOException {
    m_socket = new Socket(server, 10000);
    m_output_stream = m_socket.getOutputStream();
    m_input_stream = m_socket.getInputStream();
    m_object_output_stream = new ObjectOutputStream(m_output_stream);
    m_object_input_stream = new ObjectInputStream(m_input_stream);
  }

  boolean hasPacket() throws IOException {
    return m_input_stream.available() > 0;
  }

  Packet readPacket() throws IOException {
    try {
      return (Packet)m_object_input_stream.readObject();
    } catch (ClassNotFoundException e) {
      System.err.println(e);
      return null;
    }
  }

  void writePacket(Packet p) throws IOException {
    m_object_output_stream.writeObject(p);
  }
}
