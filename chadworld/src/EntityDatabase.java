package chadworld;

import java.util.*;
import javax.vecmath.*;


/**
 * EntityDatabase maintains a database of entities.
 */
public class EntityDatabase {

  private List m_database = new ArrayList();
  private int m_id = 0;

  synchronized Entity createEntity(String usename) {
    Entity e = new Entity();
    e.id = m_id++;
    e.transformation = new Matrix4f();
    e.transformation.setIdentity();
    return e;
  }

  synchronized void add(Entity e) {
    m_database.add(e);
  }

  synchronized void update(int id, Entity e) {
    boolean removed = false;
    for (int i = 0; i < m_database.size(); ++i) {
      Entity en = (Entity)m_database.get(i);
      if (en.id == id) {
        m_database.remove(i);
        removed = true;
        break;
      }
    }

    // don't duplicate an entity in the DB
    if (removed) {
      m_database.add(e);
    }
  }
  
}
