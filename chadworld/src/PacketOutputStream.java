package chadworld;

import java.io.*;


public class PacketOutputStream {
  private ObjectOutputStream m_os;

  public PacketOutputStream(OutputStream o) throws IOException {
    m_os = new ObjectOutputStream(o);
  }

  public void writePacket(Packet p) throws IOException {
    m_os.reset();
    m_os.writeObject(p);
  }
}
