package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * Entity objects represent the attributes of an entity in the system.
 */
public class Entity implements Serializable {
  int id;
  Point3f position = new Point3f();
  Vector3f orientation = new Vector3f();  // should be unit vector
}
