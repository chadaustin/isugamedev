package chadworld;

import java.io.*;
import java.util.*;
import javax.vecmath.*;
import javax.media.j3d.*;
import com.sun.j3d.utils.geometry.*;


/**
 * A World represents a set of world Entity objects (cubes, spheres, players).
 */
public class World implements Serializable {

  private List m_entities = new ArrayList();
  private long m_current_id = 0;
  private IDGenerator m_generator;

  World(IDGenerator gen) {
    m_generator = gen;

    // add some cubes to the world
    final int CUBE_COUNT = 20;
    for (int i = 0; i < CUBE_COUNT; ++i) {
      float px = (float)(Math.random() * 20 - 10);
      float py = (float)(Math.random() * 20 - 10);
      float pz = (float)(Math.random() * 20 - 10);
      float ax = (float)(Math.random() * Math.PI * 2);
      float ay = (float)(Math.random() * Math.PI * 2);
      float az = (float)(Math.random() * Math.PI * 2);

      Matrix4f result = new Matrix4f();
      result.setIdentity();
      result.mul(getTranslation(px, py, pz));
      result.mul(getRotX(ax));
      result.mul(getRotY(ay));
      result.mul(getRotZ(az));

      Transform3D t3d = new Transform3D(result);
      TransformGroup tgt = new TransformGroup(t3d);
      tgt.addChild(new ColorCube());
      add(new SimpleEntity(m_generator.getNext(), tgt));
    }

    // add some spheres too
    final int SPHERE_COUNT = 20;
    for (int i = 0; i < SPHERE_COUNT; ++i) {
      float px = (float)(Math.random() * 20 - 10);
      float py = (float)(Math.random() * 20 - 10);
      float pz = (float)(Math.random() * 20 - 10);
      float ax = (float)(Math.random() * Math.PI * 2);
      float ay = (float)(Math.random() * Math.PI * 2);
      float az = (float)(Math.random() * Math.PI * 2);

      Matrix4f result = new Matrix4f();
      result.setIdentity();
      result.mul(getTranslation(px, py, pz));
      result.mul(getRotX(ax));
      result.mul(getRotY(ay));
      result.mul(getRotZ(az));

      Transform3D t3d = new Transform3D(result);
      TransformGroup tgt = new TransformGroup(t3d);
      tgt.addChild(new Sphere());
      add(new SimpleEntity(m_generator.getNext(), tgt));
    }
  }

  public Iterator getEntities() {
    return m_entities.iterator();
  }

  public void add(Entity entity) {
    m_entities.add(entity);
  }

  public void remove(Entity entity) {
    m_entities.remove(entity);
  }
  
  public void remove(int id) {
    for (int i = 0; i < m_entities.size(); ++i) {
      Entity e = (Entity)m_entities.get(i);
      if (e.getID() == id) {
        m_entities.remove(e);
        return;
      }
    }
  }

  public void update(int timeElapsed) {
    for (int i = 0; i < m_entities.size(); ++i) {
      Entity e = (Entity)m_entities.get(i);
      e.update(timeElapsed);
    }
  }

  public Object get(int id) {
    for (int i = 0; i < m_entities.size(); ++i) {
      Entity e = (Entity)m_entities.get(i);
      if (e.getID() == id) {
        return e;
      }
    }
    return null;
  }

  private Matrix4f getTranslation(float x, float y, float z) {
    Matrix4f m = new Matrix4f();
    m.set(new Vector3f(x, y, z));
    return m;
  }

  private Matrix4f getRotX(float angle) {
    Matrix4f m = new Matrix4f();
    m.rotX(angle);
    return m;
  }

  private Matrix4f getRotY(float angle) {
    Matrix4f m = new Matrix4f();
    m.rotY(angle);
    return m;
  }

  private Matrix4f getRotZ(float angle) {
    Matrix4f m = new Matrix4f();
    m.rotZ(angle);
    return m;
  }

}
