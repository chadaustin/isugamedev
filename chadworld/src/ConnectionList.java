package chadworld;

import java.util.*;


public class ConnectionList {
  
  private List list = new ArrayList();

  synchronized public void add(ConnectionThread ct) {
    list.add(ct);
  }

  synchronized public void remove(ConnectionThread ct) {
    list.remove(ct);
  }

  synchronized public void sendPacket(Packet p) {
    
  }

}
