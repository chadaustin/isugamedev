package chadworld;

import java.io.*;
import javax.media.j3d.*;


public interface Entity implements Serializable {
  public int getID();
  public Node getSceneGraphNode();

  public float velocity = 0;
  public float axis_velocity = 0;
  public float axis_angle;
  public String text = "";
}
