package chadworld;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class Client {

  private JFrame m_frame;
  private JTextField m_server;

  public static void main(String[] args) {
    new Client().run();
  }

  void run() {
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

  Component createComponents() {
    JPanel pane = new JPanel();
    pane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
    pane.setLayout(new FlowLayout());

    m_server = new JTextField(30);
    JButton button = new JButton("Connect");
    button.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        String server = new String(m_server.getText());
        String[] args = { server };
        m_frame.dispose();
        chadworld.client.ChadWorldClient.main(args);
      }
    });

    pane.add(new JLabel("Enter server"));
    pane.add(m_server);
    pane.add(button);
    return pane;
  }

  void centerWindow() {
    int w = Toolkit.getDefaultToolkit().getScreenSize().width;
    int h = Toolkit.getDefaultToolkit().getScreenSize().height;

    m_frame.setLocation(new Point((w - m_frame.getSize().width) / 2,
                                  (h - m_frame.getSize().height) / 2));
                        
  }
}
