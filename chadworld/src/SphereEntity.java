package chadworld;

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


public class SphereEntity implements Entity {
  private int      m_id;
  private Matrix4f m_xform;

  public SphereEntity(int id, Matrix4f xform) {
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
    Sphere s = new Sphere();
    Appearance a = new Appearance();
    ColoringAttributes ca = new ColoringAttributes(
      0.4f, 0.6f, 0.2f,
      ColoringAttributes.NICEST);
    a.setColoringAttributes(ca);
    s.setAppearance(a);
    return s;
  }

  public void update(int timeElapsed) {
  }
}
