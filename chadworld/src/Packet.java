package chadworld;

import java.io.*;


/**
 * A packet represents a small collection of cohesive information that
 * is sent across the network.
 */
public class Packet implements Serializable {
  
  /**
   * Short text description of the packet's contents.
   */
  public String description;
}
