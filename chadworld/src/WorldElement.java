package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * A WorldElement is a static object within a World.  Right now, it
 * is limited to a cube.
 */
public class WorldElement implements Serializable {
  /**
   * The transform represents the position within the world.
   */
  Matrix4f transform;
}
