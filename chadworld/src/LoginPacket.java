package chadworld;


/**
 * Login packets contain a username and password.
 */
public class LoginPacket extends Packet {

  public LoginPacket(String u, String p) {
    username = u;
    password = p;
  }

  public String username;
  public String password;
}
