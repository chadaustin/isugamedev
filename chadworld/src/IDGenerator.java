package chadworld;


public class IDGenerator {
  private int m_current;

  public IDGenerator(int base) {
    m_current = base;
  }

  public int getNext() {
    return m_current++;
  }
}
