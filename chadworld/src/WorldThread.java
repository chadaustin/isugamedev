package chadworld;

import java.awt.event.*;
import javax.vecmath.*;
import javax.media.j3d.*;


/**
 * The world thread is responsible for handling messages from clients
 * and updating the world appropriately, sending responses to each
 * client.
 */
public class WorldThread extends Thread {
  private ConnectionList m_connection_list;
  private EntityDatabase m_entities;
  private long m_last_update;

  public WorldThread(ConnectionList cl, EntityDatabase entities) {
    m_connection_list = cl;
    m_entities = entities;
  }

  public void run() {

    m_last_update = System.currentTimeMillis();

    while (true) {
      try {
        // update at 20 frames per second
        Thread.sleep(1000 / 20);
      }
      catch (InterruptedException e) {
        // ignore interruptions
      }

      update();
    }
  }

  void update() {
    long time = System.currentTimeMillis();
    long dt = time - m_last_update;

    m_entities.updateAll(new WorldEntityUpdater(dt));

    m_last_update = time;

    // send out an "entity update" packet
    m_connection_list.sendPacket(m_entities.getUpdatePacket());
  }

  void processInputEvent(Entity e, InputPacket ip) {
    switch (ip.key) {
      case KeyEvent.VK_UP:
        e.velocity += (ip.type == InputPacket.KEY_UP ? 1 : -1);
        break;

      case KeyEvent.VK_DOWN:
        e.velocity += (ip.type == InputPacket.KEY_UP ? -1 : 1);
        break;

      case KeyEvent.VK_LEFT:
        e.axis_velocity += (ip.type == InputPacket.KEY_UP ? -1 : 1);
        break;

      case KeyEvent.VK_RIGHT:
        e.axis_velocity += (ip.type == InputPacket.KEY_UP ? 1 : -1);
        break;        
    }
  }

  void processTalkEvent(Entity e, TalkPacket tp) {
    System.out.println("processTalkEvent: " + tp.text);
    e.text = tp.text;
  }

  class WorldEntityUpdater implements EntityUpdater {
    long m_dt;

    WorldEntityUpdater(long dt) {
      m_dt = dt;
    }

    public void update(Entity e) {

      // generate orientation vector
      Vector3f orientation = new Vector3f();
      orientation.x = (float)Math.sin(e.axis_angle);
      orientation.z = (float)Math.cos(e.axis_angle);

      // update position of entity
      Vector3f dp = new Vector3f();
      dp.scale(m_dt * e.velocity / 100.0f, orientation);
      e.position.add(dp);

      // update rotation of entity
      e.axis_angle += m_dt * e.axis_velocity / 1000.0f;
    }
  }
}
