package chadworld;
import javax.media.j3d.*;


public class SimpleEntity implements Entity {
  private int m_id;
  private Node m_node;

  public SimpleEntity(int id, Node node) {
    m_id = id;
    m_node = node;
  }

  public int getID() {
    return m_id;
  }

  public Node getSceneGraphNode() {
    return m_node;
  }
}
