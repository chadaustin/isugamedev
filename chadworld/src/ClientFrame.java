package chadworld;

import java.io.*;
import java.net.*;

import java.awt.*;
import javax.swing.*;
import java.applet.Applet;
import com.sun.j3d.utils.applet.MainFrame; 
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.*;
import javax.media.j3d.*;
import javax.vecmath.*;

import java.awt.event.*;
import java.awt.AWTEvent;
import com.sun.j3d.utils.behaviors.keyboard.*;


public class ClientFrame extends Applet {

  private ServerConnection m_connection;
  private Vector3f m_orientation = new Vector3f();
  private SimpleUniverse m_universe;
  private int m_self;  // entity ID


  public static MainFrame createFrame(
    String server, int port,
    int width, int height)
  {
    ServerConnection connection = connect(server, port);
    return new MainFrame(new ClientFrame(connection), width, height);
  }

  public static ServerConnection connect(String server, int port) {
    try {
      return new ServerConnection(server, port);
    }
    catch (Exception e) {
      System.out.println("Could not connect to server");
      System.out.println(e);
      System.exit(0);
      return null;
    }
  }
  
  public ClientFrame(ServerConnection connection) {

    m_connection = connection;

    new TalkFrame(m_connection);

    try {
      // send login
      LoginPacket lp = new LoginPacket("username", "password");
      connection.writePacket(lp);

      // read response
      ResponsePacket response = (ResponsePacket)m_connection.readPacket();
      m_self = response.entity_id;
    }
    catch (Exception e) {
      System.out.println("Could not log in");
      System.out.println(e);
      System.exit(0);
    }

    // create view
    setLayout(new BorderLayout());
    Canvas3D canvas3D = new Canvas3D(
      SimpleUniverse.getPreferredConfiguration());
    add("Center", canvas3D);

    m_universe = new SimpleUniverse(canvas3D);
    BranchGroup scene = createSceneGraph(m_universe);
    m_universe.addBranchGraph(scene);
  }

  BranchGroup createSceneGraph(SimpleUniverse su) {

    BoundingSphere bigSphere = new BoundingSphere(new Point3d(), 100000);

    BranchGroup root = new BranchGroup();

    // create world synchronization behavior
    Group world = new Group();
    SynchronizationBehavior sync = new SynchronizationBehavior(
      m_connection,
      world,
      su.getViewingPlatform().getViewPlatformTransform(),
      m_self);
    sync.setSchedulingBounds(bigSphere);
    root.addChild(sync);

    // create custom navigation behavior and insert it into the scene graph
    NavigationBehavior nav = new NavigationBehavior(
      new NavigationListener() {
        public void press(int key) {
          try {
            m_connection.writePacket(
              new InputPacket(InputPacket.KEY_DOWN, key));
          }
          catch (Exception e) {
            System.out.println("Networking error sending input packet");
            System.out.println(e);
            System.exit(0);
          }
        }

        public void release(int key) {
          try {
            m_connection.writePacket(
              new InputPacket(InputPacket.KEY_UP, key));
          }
          catch (Exception e) {
            System.out.println("Networking error sending input packet");
            System.out.println(e);
            System.exit(0);
          }
        }
      }
    );
    nav.setSchedulingBounds(bigSphere);
    root.addChild(nav);

    root.addChild(world);

    ViewingPlatform vp = su.getViewingPlatform();
    TransformGroup vpTrans = vp.getViewPlatformTransform();

    // make it so we can move away from the world quite a ways and
    // still see it
    su.getViewer().getView().setBackClipDistance(100);

    // optimize the scene graph and finish
    root.compile();
    return root;
  }

}
