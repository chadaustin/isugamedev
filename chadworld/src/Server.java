package chadworld;

import chadworld.*;
import java.io.*;
import java.net.*;
import javax.vecmath.*;


public class Server {

  WorldPacket m_world = new WorldPacket();

  Server() {

    m_world.cubes = new Matrix4f[20];
    for (int i = 0; i < 20; ++i) {

      float px = (float)(Math.random() * 20 - 10);
      float py = (float)(Math.random() * 20 - 10);
      float pz = (float)(Math.random() * 20 - 10);
      float ax = (float)(Math.random() * Math.PI * 2);
      float ay = (float)(Math.random() * Math.PI * 2);
      float az = (float)(Math.random() * Math.PI * 2);

      Matrix4f result = new Matrix4f();
      result.setIdentity();
      result.mul(getTranslation(px, py, pz));
      result.mul(getRotX(ax));
      result.mul(getRotY(ay));
      result.mul(getRotZ(az));
      m_world.cubes[i] = result;

    }
  }

  Matrix4f getTranslation(float x, float y, float z) {
    Matrix4f m = new Matrix4f();
    m.set(new Vector3f(x, y, z));
    return m;
  }

  Matrix4f getRotX(float angle) {
    Matrix4f m = new Matrix4f();
    m.rotX(angle);
    return m;
  }

  Matrix4f getRotY(float angle) {
    Matrix4f m = new Matrix4f();
    m.rotY(angle);
    return m;
  }

  Matrix4f getRotZ(float angle) {
    Matrix4f m = new Matrix4f();
    m.rotZ(angle);
    return m;
  }

  void run() {

    System.out.println("Starting server...");

    try {
      ServerSocket s = new ServerSocket(10000);
      while (true) {
        new ConnectionThread(s.accept(), m_world).start();
      }
    }
    catch (Exception e) {
      System.out.println(e);
    }
  }

  public static void main(String[] args) {
    new Server().run();
  }
}
