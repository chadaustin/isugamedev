package chadworld;

import java.io.*;
import javax.media.j3d.*;


public interface Entity extends Serializable {
  public int getID();
  public Node getSceneGraphNode();
  public void update(int timeElapsed);
}
