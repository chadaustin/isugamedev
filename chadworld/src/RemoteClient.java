package chadworld;

import java.rmi.*;
import java.util.*;


interface RemoteClient extends Remote {
  void updateEntities(Iterator i) throws RemoteException;
}
