package chadworld.client;
import chadworld.*;

import java.util.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


class SynchronizationBehavior extends Behavior {

  private ServerConnection m_connection;
  private Group m_world;

  SynchronizationBehavior(ServerConnection connection, Group world) {
    m_connection = connection;
    m_world = world;

    world.setCapability(Group.ALLOW_CHILDREN_READ);
    world.setCapability(Group.ALLOW_CHILDREN_EXTEND);
    world.setCapability(Group.ALLOW_CHILDREN_WRITE);
  }

  public void initialize() {
    setWakeUp();
  }

  public void processStimulus(Enumeration criteria) {

    System.out.println("Looking for new worlds on the network...");

    // is there a new world on the network?
    try {
      while (m_connection.hasPacket()) {
        Packet p = m_connection.readPacket();

        if (p instanceof WorldPacket) {
          updateWorld((WorldPacket)p);
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
    wakeupOn(new WakeupOnElapsedTime(1000));
  }

  void updateWorld(WorldPacket wp) {

    // destroy old world
    while (m_world.numChildren() > 0) {
      m_world.removeChild(0);
    }

    BranchGroup cubeworld = new BranchGroup();

    Matrix4f[] cubes = wp.cubes;
    for (int i = 0; i < cubes.length; ++i) {
      Transform3D transform = new Transform3D(cubes[i]);
      TransformGroup tgt = new TransformGroup(transform);
      tgt.addChild(new ColorCube());
      cubeworld.addChild(tgt);
    }

    m_world.addChild(cubeworld);
  }
}
