package chadworld;

import java.awt.event.*;
import java.util.*;
import java.rmi.*;
import java.rmi.server.*;


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
  private Map m_clients = new HashMap();  // clients -> entity ids

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
    if (isAuthorized(username, password)) {
      int id = m_generator.getNext();
      m_world.add(new PlayerEntity(m_generator.getNext()));
      m_clients.put(This, new Integer(id));
      return id;
    } else {
      return -1;
    }
  }

  private boolean isAuthorized(String username, String password) {
    return true;
  }

  public synchronized void unregister(RemoteClient This) {
    Integer id = (Integer)m_clients.get(This);
    if (id != null) {
      m_world.remove(id.intValue());
    }
    m_clients.remove(This);
  }

  public synchronized void processKey(RemoteClient This, KeyEvent key) {
    Integer id = (Integer)m_clients.get(This);
    if (id != null) {
      PlayerEntity pe = (PlayerEntity)m_world.get(id.intValue());
      pe.processKey(key);
    }
  }

  public void setText(RemoteClient This, String text) {
    Integer id = (Integer)m_clients.get(This);
    if (id != null) {
      PlayerEntity pe = (PlayerEntity)m_world.get(id.intValue());
      pe.setText(text);
    }
  }

  private synchronized void update(int timeElapsed) {
    // update the objects in the world
    m_world.update(timeElapsed);

    Iterator clients = m_clients.keySet().iterator();
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
      System.err.println("Error starting server\n---" + e);
      e.printStackTrace();
    }
  }

  private static void stopServer() {
    try {
      RemoteServer rs = (RemoteServer)Naming.lookup(NAME);
      rs.stop();
      System.out.println("server stopped successfully");
    }
    catch (Exception e) {
      System.err.println("error stopping server\n---" + e);
      e.printStackTrace();
    }
  }
}
