package chadworld;

import java.util.*;
import javax.media.j3d.*;
import javax.vecmath.*;


public class CompositeEntity implements Entity {
  private int       m_id;
  private Matrix4f  m_xform;
  private ArrayList m_entities = new ArrayList();

  public CompositeEntity(int id, Matrix4f xform) {
    m_id = id;
    m_xform = xform;
  }

  public void add(Entity e) {
    m_entities.add(e);
  }

  public int getID() {
    return m_id;
  }

  public Matrix4f getTransform() {
    return m_xform;
  }

  public Node getSceneGraphNode() {
    Group g = new Group();
    for (int i = 0; i < m_entities.size(); ++i) {
      Entity e = (Entity)m_entities.get(i);
      TransformGroup tgt = new TransformGroup();
      tgt.setTransform(new Transform3D(e.getTransform()));
      tgt.addChild(e.getSceneGraphNode());
      g.addChild(tgt);
    }
    return g;
  }

  public void update(int timeElapsed) {
  }
}
