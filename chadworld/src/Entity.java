package chadworld;

import java.io.*;
import javax.media.j3d.*;
import javax.vecmath.*;


public interface Entity extends Serializable {
  public int getID();
  public Matrix4f getTransform();
  public Node getSceneGraphNode();
  public void update(int timeElapsed);
}
