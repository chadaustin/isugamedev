package chadworld;


/**
 * Input packet represents an input event.
 */
public class InputPacket extends Packet {
  static final int KEY_DOWN = 1;
  static final int KEY_UP   = 2;

  public InputPacket(int t, int k) {
    type = t;
    key = k;
  }

  int type;
  int key;  // AWT's KeyEvent types
}
