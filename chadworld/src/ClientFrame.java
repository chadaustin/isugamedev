package chadworld;

import java.io.*;
import java.net.*;
import java.rmi.*;
import java.util.*;

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


public class ClientFrame extends Applet implements RemoteClient {

  private Vector3f m_orientation = new Vector3f();
  private SimpleUniverse m_universe;
  private RemoteServer m_server;
  private int m_self;  // entity ID

  public static MainFrame createFrame(String server, int width, int height) {
    return new MainFrame(new ClientFrame(server), width, height);
  }

  public void talk(String text) {
    try {
      m_server.setText(this, text);
    }
    catch (Exception e) {
      System.err.println("setText() exception: " + e);
    }
  }

  private ClientFrame(String server) {

    try {
      String name = "//" + server + "/ChadWorldServer";
      m_server = (RemoteServer)Naming.lookup(name);
      m_self = m_server.register(this, "username", "password");
      if (m_self == -1) {
        throw new RuntimeException("Could not log into to ChadWorld server");
      }
    }
    catch (Exception e) {
      throw new RuntimeException("Could not connect to ChadWorld server " + e);
    }

    new TalkFrame(this);

    // create view
    setLayout(new BorderLayout());
    Canvas3D canvas3D = new Canvas3D(
      SimpleUniverse.getPreferredConfiguration());
    add(new JLabel("hello"), BorderLayout.NORTH);
    add("Center", canvas3D);

    m_universe = new SimpleUniverse(canvas3D);
    BranchGroup scene = createSceneGraph(m_universe);
    m_universe.addBranchGraph(scene);
  }

  // this is dumb...  needed for anonymous inner class
  private ClientFrame getThis() {
    return this;
  }

  private BranchGroup createSceneGraph(SimpleUniverse su) {

    BoundingSphere bigSphere = new BoundingSphere(new Point3d(), 100000);

    BranchGroup root = new BranchGroup();

    // create world synchronization behavior
    Group world = new Group();

    /*
    SynchronizationBehavior sync = new SynchronizationBehavior(
      world,
      su.getViewingPlatform().getViewPlatformTransform(),
      m_self);
    sync.setSchedulingBounds(bigSphere);
    root.addChild(sync);
    */

    // create custom navigation behavior and insert it into the scene graph
    NavigationBehavior nav = new NavigationBehavior(
      new NavigationListener() {
        public void onKeyEvent(KeyEvent e) {
          try {
            m_server.processKey(getThis(), e);
          }
          catch (Exception ex) {
            System.err.println("processKey() exception: " + ex);
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

  public void updateEntities(Iterator i) throws RemoteException {
    while (i.hasNext()) {
      Entity e = (Entity)i.next();
      // get the scene graph node and add it to the world
      // e.getSceneGraphNode()?
    }
  }

}
