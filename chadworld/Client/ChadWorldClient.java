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
  private BranchGroup m_sg_root;

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

  Shape3D createTree() {
    int[] counts = { 19 };
    TriangleFanArray tree = new TriangleFanArray(
      19, GeometryArray.COORDINATES | GeometryArray.COLOR_3, counts);

    tree.setCoordinate( 0, new Point3f( 0.00f, 0.60f, 0.0f ));
    tree.setCoordinate( 1, new Point3f(-0.05f, 0.00f, 0.0f ));
    tree.setCoordinate( 2, new Point3f( 0.05f, 0.00f, 0.0f ));
    tree.setCoordinate( 3, new Point3f( 0.05f, 0.25f, 0.0f ));
    tree.setCoordinate( 4, new Point3f( 0.15f, 0.30f, 0.0f ));
    tree.setCoordinate( 5, new Point3f( 0.22f, 0.25f, 0.0f ));
    tree.setCoordinate( 6, new Point3f( 0.18f, 0.40f, 0.0f ));
    tree.setCoordinate( 7, new Point3f( 0.20f, 0.55f, 0.0f ));
    tree.setCoordinate( 8, new Point3f( 0.15f, 0.65f, 0.0f ));
    tree.setCoordinate( 9, new Point3f( 0.14f, 0.80f, 0.0f ));
    tree.setCoordinate(10, new Point3f( 0.08f, 0.95f, 0.0f ));
    tree.setCoordinate(11, new Point3f( 0.00f, 1.00f, 0.0f ));
    tree.setCoordinate(12, new Point3f(-0.20f, 0.85f, 0.0f ));
    tree.setCoordinate(13, new Point3f(-0.22f, 0.70f, 0.0f ));
    tree.setCoordinate(14, new Point3f(-0.30f, 0.60f, 0.0f ));
    tree.setCoordinate(15, new Point3f(-0.35f, 0.45f, 0.0f ));
    tree.setCoordinate(16, new Point3f(-0.25f, 0.43f, 0.0f ));
    tree.setCoordinate(17, new Point3f(-0.30f, 0.25f, 0.0f ));
    tree.setCoordinate(18, new Point3f(-0.02f, 0.24f, 0.0f ));
    
    Color3f c = new Color3f(0.1f, 0.9f, 0.0f);
    for (int i = 0; i < 19; ++i) {
      tree.setColor(i, c);
    }
    c.set(0.5f, 0.5f, 0.3f);
    tree.setColor( 1, c);
    tree.setColor( 2, c);
    tree.setColor(18, c);

    return new Shape3D(tree);
  }

  Shape3D createLand() {
    LineArray land = new LineArray(
      44, GeometryArray.COORDINATES | GeometryArray.COLOR_3);

    float l = -50;
    for (int c = 0; c < 44; c += 4) {
      land.setCoordinate(c + 0, new Point3f(-50, 0, l));
      land.setCoordinate(c + 1, new Point3f( 50, 0, l));
      land.setCoordinate(c + 2, new Point3f(  l, 0, -50));
      land.setCoordinate(c + 3, new Point3f(  l, 0,  50));
      l += 10;
    }
    
    Color3f c = new Color3f(0.1f, 0.8f, 0.1f);
    for (int i = 0; i < 44; ++i) {
      land.setColor(i, c);
    }

    return new Shape3D(land);
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

    // root scene graph node
    BranchGroup objRoot = new BranchGroup();

    Transform3D T3D = new Transform3D();

    objRoot.addChild(createLand());
    SharedGroup share = new SharedGroup();
    share.addChild(createTree());

    float[][] position = {{  0.0f, 0.0f,  -3.0f},
                          {  6.0f, 0.0f,   0.0f},
                          {  6.0f, 0.0f,   6.0f},
                          {  3.0f, 0.0f, -10.0f},
                          { 13.0f, 0.0f, -30.0f},
                          {-13.0f, 0.0f,  30.0f},
                          {-13.0f, 0.0f,  23.0f},
                          { 13.0f, 0.0f,   3.0f}};

    for (int i = 0; i < position.length; ++i) {

      // create rotation transform billboard node
      TransformGroup TGR = new TransformGroup();
      TGR.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
      Billboard billboard = new Billboard(TGR);
      billboard.setSchedulingBounds(new BoundingSphere());
      TGR.addChild(new Link(share));

      // create position transform node
      T3D.setTranslation(new Vector3f(position[i]));
      TransformGroup TGT = new TransformGroup(T3D);
      TGT.addChild(TGR);

      objRoot.addChild(TGT);
      objRoot.addChild(billboard);
    }

    objRoot.addChild(createCubes());

    ViewingPlatform vp = su.getViewingPlatform();
    vp.getViewPlatform().setActivationRadius(10000);
    TransformGroup vpTrans = vp.getViewPlatformTransform();
    T3D.setTranslation(new Vector3f(0, 0.3f, 0));
    vpTrans.setTransform(T3D);

    KeyNavigatorBehavior keyNavBeh = new KeyNavigatorBehavior(vpTrans);
    keyNavBeh.setSchedulingBounds(new BoundingSphere(new Point3d(), 100000));
    objRoot.addChild(keyNavBeh);

    Background background = new Background(new Color3f(0.3f, 0.3f, 1));
    background.setApplicationBounds(new BoundingSphere(new Point3d(), 1000));
    objRoot.addChild(background);

    objRoot.compile();
    return objRoot;
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
