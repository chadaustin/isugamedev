package chadworld;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class Client {

  private JFrame m_frame;
  private JTextField m_server;
  private JTextField m_port;

  public static void main(String[] args) {
    new Client().run(args);
  }

  void run(String[] args) {
    switch (args.length) {
      // open Swing dialog and ask user for server and port
      case 0:
        startUI();
        break;

      // use specified server but default port
      case 1:
        start(args[0], Configuration.port);
        break;

      // use specified server and port
      case 2:
        start(args[0], Integer.parseInt(args[1]));
        break;

      // print usage information
      default:
        System.out.println(
          "Usage: java chadworld.Client <server> <port>" +
          "  <server> and <port> are optional");
        break;

    }
  }

  private void startUI() {
    m_frame = new JFrame("Connect to ChadWorld Server");
    m_frame.getContentPane().add(createComponents());

    m_frame.addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {
        System.exit(0);
      }
    });

    m_frame.pack();
    centerWindow();
    m_frame.setVisible(true);
  }

  private Component createComponents() {
    JPanel pane = new JPanel();
    pane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
    pane.setLayout(new FlowLayout());

    m_server = new JTextField(30);
    m_port   = new JTextField("" + Configuration.port, 30);

    JButton button = new JButton("Connect");
    button.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        // close the window
        m_frame.dispose();

        // start the chadworld client frame
        start(m_server.getText(), Integer.parseInt(m_port.getText()));
      }
    });

    pane.add(new JLabel("Enter server"));
    pane.add(m_server);
    pane.add(m_port);
    pane.add(button);
    return pane;
  }

  void centerWindow() {
    int w = Toolkit.getDefaultToolkit().getScreenSize().width;
    int h = Toolkit.getDefaultToolkit().getScreenSize().height;

    m_frame.setLocation(new Point((w - m_frame.getSize().width) / 2,
                                  (h - m_frame.getSize().height) / 2));
                        
  }

  static void start(String server, int port) {
    ClientFrame.createFrame(server, port, 640, 480);
  }
}
