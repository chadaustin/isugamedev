package chadworld;

import java.io.*;
import javax.vecmath.*;


/**
 * A World represents a set of WorldElements (cubes, houses, objects,
 * polygons, whatever) positioned relative to the origin of the world.
 * WorldElements are static objects: i.e. dynamic entities are not
 * WorldElements.
 */
public class World implements Serializable {

  public WorldElement[] elements;

  // generate randomized world of cubes
  World() {

    // number of cubes in the world
    final int ELEMENT_COUNT = 20;

    elements = new WorldElement[ELEMENT_COUNT];
    for (int i = 0; i < ELEMENT_COUNT; ++i) {
      elements[i] = new WorldElement();

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
      elements[i].transform = result;

    }
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
