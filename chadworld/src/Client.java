package chadworld;

import java.rmi.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class Client {

  public static void main(String[] args) {
    if (System.getSecurityManager() == null) {
      System.setSecurityManager(new RMISecurityManager());
    }

    try {
      if (args.length == 1) {
        connectToServer(args[0]);
      } else {
        startUI();
      }
    }
    catch (Exception e) {
      System.err.println("Exception: " + e);
    }
  }

  private static class ConnectionFrame extends JFrame {
    private JTextField m_server;

    public ConnectionFrame() {
      super("Connect to ChadWorld Server");
      getContentPane().add(createComponents());
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      pack();
    }

    public void center() {
      int w = Toolkit.getDefaultToolkit().getScreenSize().width;
      int h = Toolkit.getDefaultToolkit().getScreenSize().height;

      setLocation(new Point((w - getSize().width) / 2,
                            (h - getSize().height) / 2));
    }

    private Component createComponents() {
      JPanel pane = new JPanel();
      pane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
      pane.setLayout(new FlowLayout());

      m_server = new JTextField("localhost", 30);

      JButton button = new JButton("Connect");
      button.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          dispose();  // close the current frame

          // start the chadworld client frame
          connectToServer(m_server.getText());
        }
      });

      pane.add(new JLabel("Enter server"));
      pane.add(m_server);
      pane.add(button);
      return pane;
    }
  }

  private static void startUI() {
    ConnectionFrame frame = new ConnectionFrame();
    frame.center();
    frame.setVisible(true);
  }

  private static void connectToServer(String server) {
    ClientFrame.createFrame(server, 640, 480);
  }
}
