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


public class ClientFrame extends Applet {

  //  private Vector3f m_orientation = new Vector3f();
  private SimpleUniverse m_universe;
  private RemoteServer m_server;
  private EntityClient m_client;
  private int m_self;  // entity ID
  private TransformGroup m_view_transform;
  private Group m_world;

  public static MainFrame createFrame(String server, int width, int height) {
    return new MainFrame(new ClientFrame(server), width, height);
  }

  public void talk(String text) {
    try {
      m_server.setText(m_self, text);
    }
    catch (Exception e) {
      System.err.println("setText() exception: " + e);
      System.exit(-1);
    }
  }

  private ClientFrame(String server) {

     // log into the server
    try {
      String name = "//" + server + "/ChadWorld/Server";
      m_server = (RemoteServer)Naming.lookup(name);
      m_client = new EntityClient();
      m_self = m_server.register(m_client, "username", "password");
      if (m_self == -1) {
        throw new RuntimeException("Could not log into to ChadWorld server");
      }
    }
    catch (Exception e) {
      throw new RuntimeException("Could not connect to ChadWorld server " + e);
    }

    // create view
    setLayout(new BorderLayout());
    Canvas3D canvas3D = new Canvas3D(
      SimpleUniverse.getPreferredConfiguration());
    add(new TalkPanel(this), BorderLayout.NORTH);
    add("Center", canvas3D);

    m_universe = new SimpleUniverse(canvas3D);
    BranchGroup scene = createSceneGraph(m_universe);
    m_universe.addBranchGraph(scene);

    // now create a thread that is responsible for updating the
    // entities
    new Thread(new Runnable() {
      public void run() {
        while (true) {
          try {
            System.out.println("updating...");
            updateWorld();
            Thread.sleep(100);
          }
          catch (Exception e) {
            System.out.println("caught exception " + e);
          }
        }
      }
    }).start();
  }

  public void destroy() {
    try {
      m_server.unregister(m_self);
    }
    catch (Exception e) {
      System.err.println("Unregistration exception: " + e);
    }
  }

  private synchronized BranchGroup createSceneGraph(SimpleUniverse su) {

    BoundingSphere bigSphere = new BoundingSphere(new Point3d(), 100000);

    BranchGroup root = new BranchGroup();

    // create world synchronization behavior
    m_world = new Group();
    m_world.setCapability(Group.ALLOW_CHILDREN_READ);
    m_world.setCapability(Group.ALLOW_CHILDREN_EXTEND);
    m_world.setCapability(Group.ALLOW_CHILDREN_WRITE);

    // create custom navigation behavior and insert it into the scene graph
    NavigationBehavior nav = new NavigationBehavior(
      new NavigationListener() {
        public void onKeyEvent(KeyEvent e) {
          try {
            m_server.processKey(m_self, e);
          }
          catch (Exception ex) {
            System.err.println("processKey() exception: " + ex);
            System.exit(-1);
          }
        }
      }
    );
    nav.setSchedulingBounds(bigSphere);
    root.addChild(nav);

    /*
    Transform3D t3d = new Transform3D();
    t3d.setTranslation(new Vector3f(0, 0, -10));
    TransformGroup tgt = new TransformGroup(t3d);
    tgt.addChild(new ColorCube());
    m_world.addChild(tgt);
    */
    //    Transform3D t3d = new Transform3D();
    //t3d.setTranslation(new Vector3f(0, 0, -10));
    //TransformGroup tgt = new TransformGroup(t3d);
    //tgt.addChild(m_world);
    //root.addChild(tgt);
    root.addChild(m_world);

    ViewingPlatform vp = su.getViewingPlatform();
    m_view_transform = vp.getViewPlatformTransform();

    // make it so we can move away from the world quite a ways and
    // still see it
    su.getViewer().getView().setBackClipDistance(1000);

    // optimize the scene graph and finish
    root.compile();
    return root;
  }

  public void updateWorld() {

    // can't update the world if the scene graph doesn't exist yet!
    if (m_world == null) {
      System.out.println("null world");
      return;
    }

    BranchGroup ent_world = new BranchGroup();
    ent_world.setCapability(BranchGroup.ALLOW_DETACH);

    /*
    Transform3D t3d = new Transform3D();
    t3d.setTranslation(new Vector3d(
                         Math.random() * 20 - 10,
                         Math.random() * 20 - 10,
                         Math.random() * 20 - 10));
    TransformGroup tgt = new TransformGroup(t3d);
    tgt.addChild(new ColorCube());
    ent_world.addChild(tgt);
    m_world.addChild(ent_world);
    System.out.println("added stuff to world");
    */

    java.util.List ents = m_client.getEntities();
    for (int i = 0; i < ents.size(); ++i) {
      Entity e = (Entity)ents.get(i);

      Transform3D xform = new Transform3D(e.getTransform());

      // if we get the reference to our own entity, simply update the
      // view transform
      if (e.getID() == m_self) {
        m_view_transform.setTransform(xform);
      } else {
        TransformGroup tgt = new TransformGroup(xform);
        //tgt.addChild(new ColorCube());
        tgt.addChild(e.getSceneGraphNode());
        ent_world.addChild(tgt);
      }
    }

    // destroy old world and insert new one
    while (m_world.numChildren() > 0) {
      m_world.removeChild(0);
    }
    m_world.addChild(ent_world);
  }
}
