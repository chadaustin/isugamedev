package chadworld;

import java.util.*;
import javax.vecmath.*;


/**
 * EntityDatabase maintains a database of entities.
 */
public class EntityDatabase {

  private List m_database = new ArrayList();
  private int m_id = 0;

  /**
   * getEntity is responsible for returning the Entity object
   * associated with a username in the world.  If the EntityDatabase
   * were to store persistent locations of objects within the world,
   * getEntity() would return a new Entity object with the position
   * set to the previous position of the user.
   */
  synchronized Entity getEntity(String usename) {
    Entity e = new Entity();
    e.id = m_id++;
    m_database.add(e);
    return e;
  }

  synchronized void remove(Entity e) {
    m_database.remove(e);
  }

  synchronized void updateAll(EntityUpdater e) {
    for (int i = 0; i < m_database.size(); ++i) {
      Entity en = (Entity)m_database.get(i);
      e.update(en);
    }
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

  synchronized Packet getUpdatePacket() {
    Entity[] entities = new Entity[m_database.size()];
    for (int i = 0; i < m_database.size(); ++i) {
      entities[i] = (Entity)m_database.get(i);
    }
    return new EntityUpdatePacket(entities);
  }
  
}
