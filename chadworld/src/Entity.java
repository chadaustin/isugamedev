package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * Entity objects represent the attributes of an entity in the system.
 */
public class Entity implements Serializable {
  int id;
  Matrix4f transformation;
}
