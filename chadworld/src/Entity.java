package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * Entity objects represent the attributes of an entity in the system.
 */
public class Entity implements Serializable {

  public int id;
  public Vector3f position = new Vector3f(0, 0, 0);
  public float velocity = 0;
  public float axis_velocity = 0;
  public float axis_angle;
  public String text = "";
}
