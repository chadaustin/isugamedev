package chadworld;

import java.rmi.*;
import java.util.*;


interface RemoteClient extends Remote {
  void updateEntities(ArrayList ents) throws RemoteException;
}
