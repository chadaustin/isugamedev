package chadworld;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class TalkPanel extends JPanel {

  private ClientFrame m_client;
  private JTextField m_text;

  public TalkPanel(ClientFrame client) {
    m_client = client;

    m_text = new JTextField(30);

    JButton button = new JButton("Talk");
    button.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        m_client.talk(m_text.getText());
        m_text.setText("");
      }
    });

    add(m_text);
    add(button);
  }

}
