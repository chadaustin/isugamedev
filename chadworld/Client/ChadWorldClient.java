package chadworld.client;
import chadworld.*;

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


public class ChadWorldClient extends Applet {

  private ServerConnection m_connection;

  public ChadWorldClient(String server) {

    // connect to the server
    try {

      m_connection = new ServerConnection(server);

    } catch (Exception e) {
      System.out.println("Could not connect to server");
      System.out.println(e);
      System.exit(0);
    }

    setLayout(new BorderLayout());
    Canvas3D canvas3D = new Canvas3D(null);
    add("Center", canvas3D);

    SimpleUniverse simpleU = new SimpleUniverse(canvas3D);
    BranchGroup scene = createSceneGraph(simpleU);
    simpleU.addBranchGraph(scene);
  }

  BranchGroup createCubes() {
    BranchGroup root = new BranchGroup();
    SharedGroup share = new SharedGroup();
    share.addChild(new ColorCube());
    
    for (int i = 0; i < 20; ++i) {

      float px = (float)Math.random() * 20 - 10;
      float py = (float)Math.random() * 20 - 10;
      float pz = (float)Math.random() * 20 - 10;

      // create position transform node
      Transform3D T3D = new Transform3D();
      Transform3D rot = new Transform3D();
      T3D.setTranslation(new Vector3f(px, py, pz));
      rot.rotX(Math.random() * Math.PI * 2);
      T3D.mul(rot);
      rot.rotY(Math.random() * Math.PI * 2);
      T3D.mul(rot);
      rot.rotZ(Math.random() * Math.PI * 2);
      T3D.mul(rot);
      TransformGroup TGT = new TransformGroup(T3D);
      TGT.addChild(new Link(share));
      root.addChild(TGT);

    }
    return root;
  }

  BranchGroup createSceneGraph(SimpleUniverse su) {

    BoundingSphere bigSphere = new BoundingSphere(new Point3d(), 100000);

    BranchGroup root = new BranchGroup();

    Group world = new Group();
    //    root.addChild(createCubes());
    SynchronizationBehavior sync = new SynchronizationBehavior(
      m_connection, world);
    sync.setSchedulingBounds(bigSphere);
    root.addChild(sync);
    root.addChild(world);

    ViewingPlatform vp = su.getViewingPlatform();
    TransformGroup vpTrans = vp.getViewPlatformTransform();

    // we don't need an eye-level view
    // Transform3D T3D = new Transform3D();
    // T3D.setTranslation(new Vector3f(0, 0.3f, 0));
    // vpTrans.setTransform(T3D);

    su.getViewer().getView().setBackClipDistance(100);

    KeyNavigatorBehavior keyNav = new KeyNavigatorBehavior(vpTrans);
    keyNav.setSchedulingBounds(bigSphere);
    root.addChild(keyNav);

    root.compile();
    return root;
  }

  public static void main(String[] args) {
    System.out.println("ChadWorld Client");
    System.out.println("--");
    System.out.println("Chad Austin");
    System.out.println("Chad Okere");
    System.out.println("Hyouk-il Kwoen");
    System.out.println("Jae-ho Kwak");
    System.out.println("");

    if (args.length == 0) {
      System.out.println("Usage: java ChadWorldClient <server>");
      return;
    } else {
      new MainFrame(new ChadWorldClient(args[0]), 640, 480);
    }
  }
}
