package chadworld;

import java.io.*;


public class PacketInputStream {
  private ObjectInputStream m_is;

  public PacketInputStream(InputStream i) throws IOException {
    m_is = new ObjectInputStream(i);
  }

  public Packet readPacket() throws IOException, ClassNotFoundException {
    return (Packet)m_is.readObject();
  }
}
