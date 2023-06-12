package Java;
import javax.swing.*;
import java.awt.*;
public class expp {
    public static void main(String[] args){
    JFrame.setDefaultLookAndFeelDecorated(true);
    JFrame frm = new JFrame("yes yes");
    frm.setBounds(200,200,200,200);
    frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    JPanel panel = new JPanel();
    panel.setBorder(BorderFactory.createLineBorder(Color.blue,5));
    panel.setLayout(new GridLayout(2,1));

    JLabel label = new JLabel("Label",SwingConstants.CENTER);
    JButton button = new JButton("Button");

    panel.add(label);
    panel.add(button);
    frm.add(panel);
    frm.setVisible(true);
}
}
