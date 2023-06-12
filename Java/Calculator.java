package Java;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

public class Calculator extends JFrame {
	private final String[] Operation = { "sin", "cos", "tan", "cot", "=", "C" };
	private JPanel panel = new JPanel();// �����������
	private JTextField Interface = new JTextField();// �����ı���

	public Calculator(String title) {
		super(title);
		panel.setLayout(new GridLayout(4, 4, 20, 5));// ������壬������Ϊ���񲼾֣�5��4�У����ˮƽ����Ϊ20����ֱ����Ϊ5
		JButton[] btn1 = new JButton[10], btn2 = new JButton[6];
		for (int i = 0; i <= 9; i++)
			btn1[i] = new JButton(String.valueOf(i));// ���ְ���
		for (int i = 0; i < 10; i++) {
			btn1[i].setFont(new Font("����", Font.BOLD, 30));// �����ְ������������С
		}
		for (int i = 0; i < 6; i++)
			btn2[i] = new JButton(String.valueOf(Operation[i]));// ���Ű���
		for (int i = 0; i < 4; i++) {
			// System.out.println(Operation[i]);
			btn2[i].setFont(new Font("����", Font.BOLD, 30));// �����Ű������������С
		}
		// ����Щ��ť���������źõ�˳�򣬰����������
		for (int i = 0; i <= 9; i++)
			panel.add(btn1[i]);
		for (int i = 0; i < 6; i++)
			panel.add(btn2[i]);
		Interface.setHorizontalAlignment(JTextField.RIGHT);// �ı��������Ҳ����
		Interface.setFont(new Font("����", Font.BOLD, 30));
		Interface.setPreferredSize(new Dimension(200, 100));// �ı���Ϊ��200����100
		this.add(Interface, BorderLayout.NORTH);// ���ı�����ڿ����ĵط�
		this.add(panel, BorderLayout.CENTER);// �����������������
		this.setSize(600, 600);// ���������ڵĴ�С
		this.setResizable(true);// ��ʾ���ɵĴ����ܹ��Ƿ����û��ı��С��false��ʾ���ܣ�true������
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// ʹ�� System exit �����˳�Ӧ�ó���
		this.setVisible(true);
		for (int i = 0; i < 10; i++)
			btn1[i].addActionListener(new number());// Ϊ�¼�Դ���Ӽ�����
		for (int i = 0; i < 6; i++)
			btn2[i].addActionListener(new number());
	}

	private class number extends WindowAdapter implements ActionListener {// ��д���������������
		public void actionPerformed(ActionEvent e) {// �����ActionListener����ӿ�����ķ���,��������ķ���
			if (!e.getActionCommand().equals("=") && !e.getActionCommand().equals("C")
					&& !e.getActionCommand().equals("<-")) {
				Interface.setText(Interface.getText() + e.getActionCommand());// ���ı�������ʾ
			} //
			else if (e.getActionCommand().equals("<-")) {
				String Formula = Interface.getText();
				int len = Formula.length();
				if (len != 0) {
					String s = String.valueOf(Formula.substring(0, len - 1));
					Interface.setText(s);
				}
			} else if (e.getActionCommand().equals("=")) {
				String Formula = Interface.getText();
				if (Formula.contains("sin")) {
					double number = Double.parseDouble(Formula.substring(Formula.indexOf('n') + 1));
					double a = Math.toRadians(number);
					Interface.setText(String.valueOf(Math.sin(a)));
				} else if (Formula.contains("cos")) {
					double number = Double.parseDouble(Formula.substring(Formula.indexOf('s') + 1));
					double a = Math.toRadians(number);
					Interface.setText(String.valueOf(Math.cos(a)));
				} else if (Formula.contains("tan")) {
					double number = Double.parseDouble(Formula.substring(Formula.indexOf('n') + 1));
					double a = Math.toRadians(number);
					Interface.setText(String.valueOf(Math.tan(a)));
				} else if (Formula.contains("cot")) {
					double number = Double.parseDouble(Formula.substring(Formula.indexOf('t') + 1));
					double a = Math.toRadians(number);
					Interface.setText(String.valueOf(1/Math.tan(a)));  //һֱ����
				}

			} else {
				Interface.setText(null);
			}
		}
	}

	public static void main(String[] args) {
		new Calculator("�����Ǻ���������");
	}
}
