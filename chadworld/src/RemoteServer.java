package chadworld;

import java.awt.event.*;
import java.rmi.*;


interface RemoteServer extends Remote {
  int register(RemoteClient This, String username, String password)
    throws RemoteException;
  void unregister(RemoteClient This)
    throws RemoteException;
  void processKey(RemoteClient This, KeyEvent key)
    throws RemoteException;
  void setText(RemoteClient This, String text)
    throws RemoteException;
  void stop()
    throws RemoteException;
}
