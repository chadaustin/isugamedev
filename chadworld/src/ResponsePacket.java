package chadworld;


/**
 * A response packet contains information that the server sends back
 * after a successful login.
 */
public class ResponsePacket extends Packet {

  public ResponsePacket(int id) {
    entity_id = id;
  }

  public int entity_id;
}
