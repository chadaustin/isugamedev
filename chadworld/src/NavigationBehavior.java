package chadworld;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.geometry.*;


public class NavigationBehavior extends Behavior {

  private NavigationListener m_listener;
  private WakeupOnAWTEvent m_key_criterion;

  boolean[] m_pressed     = new boolean[512];
  boolean[] m_old_pressed = new boolean[512];

  public NavigationBehavior(NavigationListener nl) {
    m_listener = nl;
    m_key_criterion = new WakeupOnAWTEvent(AWTEvent.KEY_EVENT_MASK);
  }

  public void initialize() {
    wakeupOn(m_key_criterion);
  }

  public void processStimulus(Enumeration criteria) {

    try {

      // store the current keypress states
      for (int i = 0; i < 512; ++i) {
        m_old_pressed[i] = m_pressed[i];
      }

      // update the keypress states
      AWTEvent[] events = m_key_criterion.getAWTEvent();
      for (int i = 0; i < events.length; ++i) {
        KeyEvent e = (KeyEvent)events[i];
        int kc = e.getKeyCode();
        if (kc >= 0 && kc < 512) {
          if (e.getID() == KeyEvent.KEY_PRESSED) {
            m_pressed[kc] = true;
          } else if (e.getID() == KeyEvent.KEY_RELEASED) {
            m_pressed[kc] = false;
          }
        }
      }

      // notify listener of key changes
      for (int i = 0; i < 512; ++i) {
        if (m_old_pressed[i] != m_pressed[i]) {
          if (m_pressed[i]) {  // PRESS
            m_listener.press(i);
          } else {             // RELEASE
            m_listener.release(i);
          }
        }
      }

    }
    catch (Exception e) {
      // do nothing!
    }

    initialize();
  }

}
