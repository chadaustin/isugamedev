package chadworld;

import java.util.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


class SynchronizationBehavior extends Behavior {

  private ServerConnection m_connection;
  private Group m_world;
  private Group m_static_world;
  private Group m_dynamic_world;
  private TransformGroup m_view_transform;
  private int m_entity_id;

  public SynchronizationBehavior(
    ServerConnection connection,
    Group world,
    TransformGroup view_transform,
    int entity_id)
  {
    m_connection = connection;
    m_world = world;
    m_view_transform = view_transform;
    m_entity_id = entity_id;

    setChildCaps(world);

    m_world.addChild(m_static_world  = createMutableGroup());
    m_world.addChild(m_dynamic_world = createMutableGroup());
  }

  private Group createMutableGroup() {
    Group g = new Group();
    setChildCaps(g);
    return g;
  }

  private void setChildCaps(Group g) {
    g.setCapability(Group.ALLOW_CHILDREN_READ);
    g.setCapability(Group.ALLOW_CHILDREN_EXTEND);
    g.setCapability(Group.ALLOW_CHILDREN_WRITE);
  }

  public void initialize() {
    setWakeUp();
  }

  public void processStimulus(Enumeration criteria) {

    try {
      // are there packets on the network?
      while (m_connection.hasPacket()) {
        Packet p = m_connection.readPacket();

        if (p instanceof WorldPacket) {
          System.out.println("Found world!");
          updateWorld((WorldPacket)p);
        } else if (p instanceof EntityUpdatePacket) {
          updateEntities((EntityUpdatePacket)p);
        }
      }
    }
    catch (Exception e) {
      System.err.println(e);
      System.exit(0);
    }
    
    setWakeUp();
  }

  void setWakeUp() {
    wakeupOn(new WakeupOnElapsedTime(50));
  }

  void updateWorld(WorldPacket wp) {

    // destroy old world
    while (m_static_world.numChildren() > 0) {
      m_static_world.removeChild(0);
    }

    BranchGroup cubeworld = new BranchGroup();
    cubeworld.setCapability(BranchGroup.ALLOW_DETACH);

    WorldElement[] cubes = wp.world.elements;
    for (int i = 0; i < cubes.length; ++i) {
      Transform3D transform = new Transform3D(cubes[i].transform);
      TransformGroup tgt = new TransformGroup(transform);
      tgt.addChild(new ColorCube());
      
      cubeworld.addChild(tgt);
    }

    m_static_world.addChild(cubeworld);
  }

  void updateEntities(EntityUpdatePacket eup) {

    // destroy old world
    while (m_dynamic_world.numChildren() > 0) {
      m_dynamic_world.removeChild(0);
    }

    BranchGroup coneworld = new BranchGroup();
    coneworld.setCapability(BranchGroup.ALLOW_DETACH);

    for (int i = 0; i < eup.entities.length; ++i) {
      Entity e = eup.entities[i];

      // is this ourself?
      if (e.id == m_entity_id) {

        // update view transform
        Transform3D t3d = new Transform3D();
        t3d.rotY(e.axis_angle);
        t3d.setTranslation(eup.entities[i].position);
        m_view_transform.setTransform(t3d);

      // otherwise add a cone to the scene graph
      } else {

        // set up the transformation
        Transform3D t1 = new Transform3D();
        Transform3D t2 = new Transform3D();
        t1.rotY(e.axis_angle);
        t2.rotX(-Math.PI / 2);
        t1.mul(t2);
        t1.setTranslation(eup.entities[i].position);

        // stick it in the scene graph
        TransformGroup tgt = new TransformGroup(t1);
        tgt.addChild(createWhiteCone());
        coneworld.addChild(tgt);

      }
    }

    m_dynamic_world.addChild(coneworld);
  }

  private Cone createWhiteCone() {
    Cone c = new Cone();
    Appearance a = new Appearance();
    ColoringAttributes ca = new ColoringAttributes(
      0.9f, 0.9f, 0.9f,
      ColoringAttributes.NICEST);
    a.setColoringAttributes(ca);
    c.setAppearance(a);
    return c;
  }
}
