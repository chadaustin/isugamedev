package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * Entity objects represent the attributes of an entity in the system.
 */
public class Entity implements Serializable {

  int id;
  Vector3f position = new Vector3f(0, 0, 0);
  float velocity = 0;
  float axis_velocity = 0;
  float axis_angle;
  String text = "";
}
