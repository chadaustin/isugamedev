package chadworld;

import java.util.*;
import java.rmi.*;
import java.rmi.server.*;


public class EntityClient
  extends UnicastRemoteObject 
  implements RemoteClient
{
  private List m_entities;

  public EntityClient() throws RemoteException {
  }

  public void updateEntities(ArrayList ents) throws RemoteException {
    m_entities = ents;
  }

  public List getEntities() {
    return m_entities;
  }
}
