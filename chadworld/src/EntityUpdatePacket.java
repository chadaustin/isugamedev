package chadworld;


/**
 * Entity update packets contain positions and orientations of all
 * dynamic entities within the world.
 */
public class EntityUpdatePacket extends Packet {
  Entity[] entities;
}
