package chadworld;
import java.rmi.*;

interface RemoteClient extends Remote {
  void updateEntities(Iterator i) throws RemoteException;
}
