package chadworld.client;
import chadworld.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


public class NavigationBehavior extends Behavior {

  private NavigationListener m_listener;
  private WakeupOnAWTEvent m_key_criterion;
  private WakeupCriterion m_frame_criterion;

  private float m_forward_velocity;
  private long m_last_time;

  public NavigationBehavior(NavigationListener nl) {
    m_listener = nl;
    m_key_criterion = new WakeupOnAWTEvent(KeyEvent.KEY_PRESSED);
    m_frame_criterion = new WakeupOnElapsedFrames(1);
  }

  public void initialize() {
    setWakeUp();

    m_last_time = System.currentTimeMillis();
  }

  public void setWakeUp() {
    WakeupCriterion[] cond = { m_key_criterion, m_frame_criterion };
    wakeupOn(new WakeupOr(cond));
  }

  public void processStimulus(Enumeration criteria) {
    while (criteria.hasMoreElements()) {
      Object element = criteria.nextElement();
      System.out.println(element.getClass());
      if (element.equals(m_key_criterion)) {

        try {

          // get the key
          AWTEvent[] events = m_key_criterion.getAWTEvent();
          KeyEvent e = (KeyEvent)events[0];
          if (e.getID() == KeyEvent.KEY_PRESSED) {
          
            switch (e.getKeyCode()) {
              case KeyEvent.VK_UP:   m_forward_velocity += 1; break;
              case KeyEvent.VK_DOWN: m_forward_velocity -= 1; break;
            }

          } else if (e.getID() == KeyEvent.KEY_RELEASED) {

            switch (e.getKeyCode()) {
              case KeyEvent.VK_UP:   m_forward_velocity -= 1; break;
              case KeyEvent.VK_DOWN: m_forward_velocity += 1; break;
            }

          }

        }
        catch (Exception e) {
          // do nothing!
        }

      }
      if (element.equals(m_frame_criterion)) {

        System.out.println(m_forward_velocity);

        // update position or something
        if (m_forward_velocity != 0) {
          long time = System.currentTimeMillis();
          m_listener.update(
            new Vector3f((time - m_last_time) * m_forward_velocity, 0, 0));
          m_last_time = time;
        }

      }

    }

    setWakeUp();
  }

}
