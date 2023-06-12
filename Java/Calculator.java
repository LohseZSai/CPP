package Java;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

public class Calculator extends JFrame {
	private final String[] Operation = { "sin", "cos", "tan", "cot", "=", "C" };
	private JPanel panel = new JPanel();// 创建面板容器
	private JTextField Interface = new JTextField();// 创建文本框

	public Calculator(String title) {
		super(title);
		panel.setLayout(new GridLayout(4, 4, 20, 5));// 定义面板，并设置为网格布局，5行4列，组件水平距离为20，垂直距离为5
		JButton[] btn1 = new JButton[10], btn2 = new JButton[6];
		for (int i = 0; i <= 9; i++)
			btn1[i] = new JButton(String.valueOf(i));// 数字按键
		for (int i = 0; i < 10; i++) {
			btn1[i].setFont(new Font("黑体", Font.BOLD, 30));// 给数字按键调整字体大小
		}
		for (int i = 0; i < 6; i++)
			btn2[i] = new JButton(String.valueOf(Operation[i]));// 符号按键
		for (int i = 0; i < 4; i++) {
			// System.out.println(Operation[i]);
			btn2[i].setFont(new Font("黑体", Font.BOLD, 30));// 给符号按键调整字体大小
		}
		// 把这些按钮按照事先排好的顺序，按在面板容器
		for (int i = 0; i <= 9; i++)
			panel.add(btn1[i]);
		for (int i = 0; i < 6; i++)
			panel.add(btn2[i]);
		Interface.setHorizontalAlignment(JTextField.RIGHT);// 文本框内容右侧对齐
		Interface.setFont(new Font("黑体", Font.BOLD, 30));
		Interface.setPreferredSize(new Dimension(200, 100));// 文本框为宽200，长100
		this.add(Interface, BorderLayout.NORTH);// 将文本框放在靠北的地方
		this.add(panel, BorderLayout.CENTER);// 将面板容器放在中央
		this.setSize(600, 600);// 设置主窗口的大小
		this.setResizable(true);// 表示生成的窗体能够是否有用户改变大小，false表示不能，true代表能
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 使用 System exit 方法退出应用程序。
		this.setVisible(true);
		for (int i = 0; i < 10; i++)
			btn1[i].addActionListener(new number());// 为事件源增加监听器
		for (int i = 0; i < 6; i++)
			btn2[i].addActionListener(new number());
	}

	private class number extends WindowAdapter implements ActionListener {// 重写监听器里面的内容
		public void actionPerformed(ActionEvent e) {// 这个是ActionListener这个接口里面的方法,监听器里的方法
			if (!e.getActionCommand().equals("=") && !e.getActionCommand().equals("C")
					&& !e.getActionCommand().equals("<-")) {
				Interface.setText(Interface.getText() + e.getActionCommand());// 在文本框中显示
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
					Interface.setText(String.valueOf(1/Math.tan(a)));  //一直报错
				}

			} else {
				Interface.setText(null);
			}
		}
	}

	public static void main(String[] args) {
		new Calculator("简单三角函数计算器");
	}
}
