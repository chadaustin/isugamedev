package chadworld;
import java.rmi.*;

interface RemoteServer extends Remote {
  int register(RemoteClient This, String username, String password)
    throws RemoteException;
  void unregister(int id)
    throws RemoteException;
  void processKey(int id, KeyEvent key)
    throws RemoteException;
  void stop()
    throws RemoteException;
}