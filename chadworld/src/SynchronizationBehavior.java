package chadworld;

import java.util.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


class SynchronizationBehavior extends Behavior {

  private ServerConnection m_connection;
  private Group m_world;
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

    world.setCapability(Group.ALLOW_CHILDREN_READ);
    world.setCapability(Group.ALLOW_CHILDREN_EXTEND);
    world.setCapability(Group.ALLOW_CHILDREN_WRITE);
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
          updateWorld((WorldPacket)p);
          System.out.println("Found world!");
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
    while (m_world.numChildren() > 0) {
      m_world.removeChild(0);
    }

    BranchGroup cubeworld = new BranchGroup();

    WorldElement[] cubes = wp.world.elements;
    for (int i = 0; i < cubes.length; ++i) {
      Transform3D transform = new Transform3D(cubes[i].transform);
      TransformGroup tgt = new TransformGroup(transform);
      tgt.addChild(new ColorCube());
      cubeworld.addChild(tgt);
    }

    m_world.addChild(cubeworld);
  }

  void updateEntities(EntityUpdatePacket eup) {
    for (int i = 0; i < eup.entities.length; ++i) {
      if (eup.entities[i].id == m_entity_id) {

        // update view transform
        Transform3D t3d = new Transform3D();
        t3d.set(eup.entities[i].position);
        m_view_transform.setTransform(t3d);

      }
    }
  }
}
