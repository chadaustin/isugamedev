package chadworld;

import java.awt.*;
import java.awt.event.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


public class PlayerEntity implements Entity {
  private int m_id;

  private Vector3f m_position = new Vector3f();
  private float m_velocity = 0;
  private float m_axis_velocity = 0;
  private float m_axis_angle;
  private String m_text = "";

  public PlayerEntity(int id) {
    m_id = id;
  }

  public int getID() {
    return m_id;
  }

  public Matrix4f getTransform() {
    // set up the transformation
    Matrix4f t1 = new Matrix4f();
    Matrix4f t2 = new Matrix4f();
    t1.rotY(-m_axis_angle);
    //    t2.rotX((float)(-Math.PI / 2));
    //    t1.mul(t2);
    t1.setTranslation(m_position);
    return t1;
  }

  public Node getSceneGraphNode() {
    Group g = new Group();
    g.addChild(createWhiteCone());
    g.addChild(createRaisedText(m_text));
    return g;
  }

  public void update(int timeElapsed) {
    m_position.x += timeElapsed * m_velocity * Math.sin(m_axis_angle);
    m_position.z -= timeElapsed * m_velocity * Math.cos(m_axis_angle);
    m_axis_angle += timeElapsed * m_axis_velocity;
  }

  public void processKey(KeyEvent key) {
    if (key.getID() == KeyEvent.KEY_PRESSED) {
      switch (key.getKeyCode()) {
        case KeyEvent.VK_UP:    m_velocity      =  0.005f; break;
        case KeyEvent.VK_DOWN:  m_velocity      = -0.005f; break;
        case KeyEvent.VK_LEFT:  m_axis_velocity = -0.001f; break;
        case KeyEvent.VK_RIGHT: m_axis_velocity =  0.001f; break;
      }
    } else {
      switch (key.getKeyCode()) {
        case KeyEvent.VK_UP:    m_velocity      = 0; break;
        case KeyEvent.VK_DOWN:  m_velocity      = 0; break;
        case KeyEvent.VK_LEFT:  m_axis_velocity = 0; break;
        case KeyEvent.VK_RIGHT: m_axis_velocity = 0; break;
      }
    }
  }

  public void setText(String text) {
    m_text = text;
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

  private TransformGroup createRaisedText(String text) {

    Font3D font3D = new Font3D(
      new Font("Helvetica", Font.PLAIN, 1),
      new FontExtrusion());
    ColoringAttributes textColor = new ColoringAttributes(
      1, 1, 1, ColoringAttributes.NICEST);
    Appearance textAppear = new Appearance();

    textAppear.setColoringAttributes(textColor);
    Text3D textGeom = new Text3D(font3D, new String(text));
    textGeom.setAlignment(Text3D.ALIGN_CENTER);

    Transform3D t3d = new Transform3D();
    t3d.rotX(Math.PI / 2);
    t3d.setTranslation(new Vector3f(0, 0, 1));
    TransformGroup tg = new TransformGroup(t3d);
    tg.addChild(new Shape3D(textGeom, textAppear));
    return tg;
  }
}
