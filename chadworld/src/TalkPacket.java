package chadworld;


/**
 * The talk packet represents saying something within the world.  The
 * server receives the talk packet and updates the entity state with
 * the "spoken" text.
 */
public class TalkPacket extends Packet {

  public TalkPacket(String t) {
    text = t;
  }

  public String text;
}
