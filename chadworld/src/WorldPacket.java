package chadworld;


/**
 * World packets contain a copy of the entire static world.
 */
public class WorldPacket extends Packet {

  public World world;

  public WorldPacket(World w) {
    world = w;
    description = "World Description";
  }
}
