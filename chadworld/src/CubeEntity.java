package chadworld;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


public class CubeEntity implements Entity {
  private int      m_id;
  private Matrix4f m_xform;

  public CubeEntity(int id, Matrix4f xform) {
    m_id    = id;
    m_xform = xform;
  }

  public int getID() {
    return m_id;
  }

  public Matrix4f getTransform() {
    return m_xform;
  }

  public Node getSceneGraphNode() {
    return new ColorCube();
  }

  public void update(int timeElapsed) {
  }
}
