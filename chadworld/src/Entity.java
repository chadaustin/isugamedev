package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * Entity objects represent the attributes of an entity in the system.
 */
public class Entity implements Serializable {

  int id;
  Vector3f position    = new Vector3f();
  Vector3f orientation = new Vector3f();  // should be unit vector
  Vector3f velocity    = new Vector3f();
}
