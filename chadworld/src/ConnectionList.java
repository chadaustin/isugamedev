package chadworld;

import java.util.*;


public class ConnectionList {
  
  private List m_list = new ArrayList();

  synchronized public void add(ConnectionThread ct) {
    m_list.add(ct);
  }

  synchronized public void remove(ConnectionThread ct) {
    m_list.remove(ct);
  }

  synchronized public void sendPacket(Packet p) {
    for (int i = 0; i < m_list.size(); ++i) {
      ConnectionThread ct = (ConnectionThread)m_list.get(i);
      ct.sendPacket(p);
    }
  }

}
