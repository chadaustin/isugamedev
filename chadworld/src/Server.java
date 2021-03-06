package chadworld;

import java.awt.event.*;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;
import javax.vecmath.*;


/**
 * The server application. It keeps a synchronized copy of the world.
 * It also registers itself with the RMI naming server so that clients
 * can connect.
 */
public class Server
  extends UnicastRemoteObject
  implements RemoteServer
{
  private static final String NAME = "//localhost/ChadWorld/Server";

  private IDGenerator m_generator = new IDGenerator(100);
  private World m_world = new World(m_generator);
  private Map m_clients = new HashMap();  // entity ids -> clients

  private Server() throws RemoteException {

    // create a thread that calls update() periodically
    new Thread(new Runnable() {
      public void run() {
        long lastUpdate = System.currentTimeMillis();
        while (true) {
          long now = System.currentTimeMillis();
          update((int)(now - lastUpdate));
          try {
            Thread.sleep(100);
          }
          catch (Exception e) {
            // ignore thread interrupted exceptions
          }
          lastUpdate = now;
        }
      }
    }).start();

  }

  public synchronized int register(
    RemoteClient This,
    String username,
    String password)
  {
    System.out.println("Player '" + username + "' is registering...");

    if (isAuthorized(username, password)) {
      int id = m_generator.getNext();
      m_world.add(new PlayerEntity(id));
      m_clients.put(new Integer(id), This);
      System.out.println("  successfully registered with entity id = " + id);
      return id;
    } else {
      return -1;
    }
  }

  private boolean isAuthorized(String username, String password) {
    return true;
  }

  public synchronized void unregister(int id) {
    RemoteClient This = (RemoteClient)m_clients.get(new Integer(id));
    if (This != null) {
      m_world.remove(id);
    }
    m_clients.remove(new Integer(id));
    System.out.println("Player with entity id " + id + " unregistered");
  }

  public synchronized void processKey(int id, KeyEvent key) {
    RemoteClient This = (RemoteClient)m_clients.get(new Integer(id));
    if (This != null) {
      PlayerEntity pe = (PlayerEntity)m_world.get(id);

      if (key.getID() == KeyEvent.KEY_PRESSED) {
        switch (key.getKeyCode()) {
          case KeyEvent.VK_C:
            System.out.println("C pressed");
            m_world.add(
              new CubeEntity(m_generator.getNext(), pe.getTransform()));
            return;
            
          case KeyEvent.VK_S:
            System.out.println("S pressed");
            m_world.add(
              new SphereEntity(m_generator.getNext(), pe.getTransform()));
            return;

          case KeyEvent.VK_X:
            System.out.println("X pressed");
            m_world.add(createComposite(pe.getTransform()));
            return;
        }
      }

      if (pe != null) {
        pe.processKey(key);
      }
    }
  }

  private Entity createComposite(Matrix4f xform) {
    CompositeEntity ce = new CompositeEntity(m_generator.getNext(), xform);
    ce.add(translatedCube(-1, -1, -1));
    ce.add(translatedCube(-1, -1,  1));
    ce.add(translatedCube(-1,  1, -1));
    ce.add(translatedCube(-1,  1,  1));
    ce.add(translatedCube( 1, -1, -1));
    ce.add(translatedCube( 1, -1,  1));
    ce.add(translatedCube( 1,  1, -1));
    ce.add(translatedCube( 1,  1,  1));
    return ce;
  }

  private Entity translatedCube(int x, int y, int z) {
    Matrix4f xform = new Matrix4f();
    xform.setIdentity();
    xform.setTranslation(new Vector3f(x * 2, y * 2, z * 2));
    return new CubeEntity(m_generator.getNext(), xform);
  }

  public void setText(int id, String text) {
    RemoteClient This = (RemoteClient)m_clients.get(new Integer(id));
    if (This != null) {
      PlayerEntity pe = (PlayerEntity)m_world.get(id);
      if (pe != null) {
        pe.setText(text);
      }
    }
  }

  private synchronized void update(int timeElapsed) {
    // update the objects in the world
    m_world.update(timeElapsed);

    Iterator clients = m_clients.values().iterator();
    while (clients.hasNext()) {
      RemoteClient rc = (RemoteClient)clients.next();
      try {
        rc.updateEntities(m_world.getEntities());
      }
      catch (RemoteException e) {
        // network error?  remove the offending connection!
        clients.remove();
      }
    }
  }

  public void stop() {
    try {
      System.out.println("Stopping...");
      Naming.unbind(NAME);
      System.exit(0);
    }
    catch (Exception e) {
      System.err.println("Error stopping server\n---" + e);
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    // make sure the user passed in the correct arguments
    if (args.length != 1) {
      System.out.println(
        "Usage:\n" +
        "    java chadworld.Server <command>\n" +
        "where <command> is one of:\n" +
        "    run  - creates server object and waits for connections\n" +
        "    stop - halts server\n");
      return;
    }

    // set security manager to the RMI one if it doesn't exist
    if (System.getSecurityManager() == null) {
      System.setSecurityManager(new RMISecurityManager());
    }

    String command = args[0];
    if (command.equals("run")) {
      runServer();
    } else if (command.equals("stop")) {
      stopServer();
    } else {
      System.out.println("Invalid command '" + command + "'");
    }
  }

  private static void runServer() {
    try {
      Naming.bind(NAME, new Server());
      System.out.println("Server started");
    }
    catch (Exception e) {
      System.err.println("Error starting server\n---\n" + e);
    }
  }

  private static void stopServer() {
    try {
      RemoteServer rs = (RemoteServer)Naming.lookup(NAME);
      rs.stop();
      System.out.println("server stopped successfully");
    }
    catch (Exception e) {
      System.err.println("error stopping server\n---\n" + e);
    }
  }
}
