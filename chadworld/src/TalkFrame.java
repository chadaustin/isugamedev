package chadworld;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class TalkFrame extends JFrame {

  private ServerConnection m_connection;
  private JTextField m_text;

  public TalkFrame(ServerConnection connection) {
    super("Talk");

    m_connection = connection;

    getContentPane().add(createComponents());
    setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
    pack();
    setVisible(true);
  }

  private Component createComponents() {
    JPanel pane = new JPanel();
    pane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
    pane.setLayout(new FlowLayout());

    m_text = new JTextField(30);
    JButton talk = new JButton("Talk");
    talk.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
	String text = m_text.getText();
	
        // send TalkPacket to server
	try {
	  m_connection.writePacket(new TalkPacket(text));
	  m_text.setText("");
	}
	catch (Exception ex) {
	  System.out.println("Error sending talk packet!");
	  System.out.println(ex);
	  System.exit(0);
	}
      }
    });

    pane.add(m_text);
    pane.add(talk);
    return pane;
  }

}
