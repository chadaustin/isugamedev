package chadworld;

import java.io.*;
import java.net.*;

import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.Frame;
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


  public static MainFrame createFrame(String server, int width, int height) {
    return new MainFrame(new ClientFrame(server), width, height);
  }


  public ClientFrame(String server) {

    // connect to the server
    try {

      m_connection = new ServerConnection(server);

    } catch (Exception e) {
      System.out.println("Could not connect to server");
      System.out.println(e);
      System.exit(0);
    }

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

    Group world = new Group();
    SynchronizationBehavior sync = new SynchronizationBehavior(
      m_connection, world);
    sync.setSchedulingBounds(bigSphere);
    root.addChild(sync);

    NavigationBehavior nav = new NavigationBehavior(
      new NavigationListener() {
        public void press(int key) {
          System.out.println("pressed " + key);
        }

        public void release(int key) {
          System.out.println("unpressed " + key);
        }
      }
    );
    nav.setSchedulingBounds(bigSphere);
    root.addChild(nav);

    root.addChild(world);

    ViewingPlatform vp = su.getViewingPlatform();
    TransformGroup vpTrans = vp.getViewPlatformTransform();

    su.getViewer().getView().setBackClipDistance(100);

    root.compile();
    return root;
  }

}
