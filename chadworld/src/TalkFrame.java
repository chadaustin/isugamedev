package chadworld;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class TalkFrame extends JFrame {

  private ClientFrame m_client;
  private JTextField m_text;

  public TalkFrame(ClientFrame client) {
    super("Talk");
    m_client = client;

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
        m_client.talk(m_text.getText());
        m_text.setText("");
      }
    });

    pane.add(m_text);
    pane.add(talk);
    return pane;
  }

}
