package chadworld.test;
import chadworld.*;

import junit.framework.*;


public class EntityDatabaseTest extends TestCase {

  private int m_chad_id;

  public EntityDatabaseTest(String name) {
    super(name);
  }

  public void testDB() {
    EntityDatabase db = new EntityDatabase();
    Entity e1 = db.getEntity("chad");
    Entity e2 = db.getEntity("notchad");
    assertTrue(e1 != e2);

    m_chad_id = e1.id;

    db.remove(e2);
    db.updateAll(new EntityUpdater() {
      public void update(Entity e) {
        assertTrue(e.id == m_chad_id);
      }
    });
  }

  public static Test suite() {
    return new TestSuite(EntityDatabaseTest.class);
  }
}
