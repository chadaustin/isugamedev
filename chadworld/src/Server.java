package chadworld;

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

  private World m_world = new World();
  private List m_clients = new ArrayList();

  ConnectionList m_connection_list = new ConnectionList();
  WorldThread m_world_thread;

  private Server() {

    // create a thread that calls update() periodically
    new Thread(new Runnable() {
      public void run() {
        long lastUpdate = System.currentTimeMillis();
        while (true) {
          long now = System.currentTimeMillis();
          update(now - lastUpdate);
          Thread.sleep(100);
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
      m_world.add(
      m_clients.add(This);
      return m_clients.size() - 1;
    } else {
      return -1;
    }
  }

  private boolean isAuthorized(String username, String password) {
    return true;
  }

  public synchronized void unregister(int id) {
    m_clients.remove(id);
  }

  public synchronized void processKey(int id, KeyEvent key) {
    RemoteClient rc = (RemoteClient)m_clients.get(id);
    
    switch (key) {
      case KeyEvent.VK_UP:
        
    }
  }

  private synchronized void update(int timeElapsed) {
    // update the objects in the world
    m_world.update(timeElapsed);

    // for each client, send the new entities
    for (int i = 0; i < m_clients.size(); ++i) {
      RemoteClient rc = (RemoteClient)m_clients.get(i);
      try {
        rc.updateEntities(m_world.getEntities());
      }
      catch (RemoteException re) {
        // if we couldn't operate on the client, remove it from the list
        m_clients.remove(i);
        --i;
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
        "Usage:" +
        "    java chadworld.Server <command>" +
        "where <command> is one of:" +
        "    run  - creates server object and waits for connections" +
        "    stop - halts server");
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
      remoteserver rs = (remoteserver)naming.lookup(name);
      rs.shutdown();
      system.out.println("server stopped successfully");
    }
    catch (exception e) {
      system.err.println("error stopping server\n---" + e);
      e.printstacktrace();
    }
  }
}
