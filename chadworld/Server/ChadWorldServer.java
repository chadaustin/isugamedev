package chadworld.server;

import java.io.*;
import java.net.*;


public class ChadWorldServer {

  void run() {

    System.out.println("Starting server...");

    try {
      ServerSocket s = new ServerSocket(10000);
      while (true) {
        new ConnectionThread(s.accept()).start();
        System.out.println("Accepted connection");
      }
    }
    catch (Exception e) {
      System.out.println(e);
    }
  }

  public static void main(String[] args) {
    new ChadWorldServer().run();
  }
}
