package chadworld;

import java.io.*;
import java.net.*;


class ServerConnection {
  private Socket m_socket;
  private OutputStream m_output_stream;
  private InputStream m_input_stream;
  private PacketOutputStream m_packet_output_stream;
  private PacketInputStream m_packet_input_stream;

  ServerConnection(String server, int port) throws IOException {
    m_socket = new Socket(server, port);
    m_output_stream = m_socket.getOutputStream();
    m_input_stream = m_socket.getInputStream();
    m_packet_output_stream = new PacketOutputStream(m_output_stream);
    m_packet_input_stream = new PacketInputStream(m_input_stream);
  }

  boolean hasPacket() throws IOException {
    return m_input_stream.available() > 0;
  }

  Packet readPacket() throws IOException {
    try {
      return (Packet)m_packet_input_stream.readPacket();
    } catch (ClassNotFoundException e) {
      System.err.println(e);
      return null;
    }
  }

  void writePacket(Packet p) throws IOException {
    m_packet_output_stream.writePacket(p);
  }
}
