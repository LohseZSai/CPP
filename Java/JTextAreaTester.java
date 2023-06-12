package Java;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.*;
import javax.swing.plaf.basic.BasicComboBoxUI.ItemHandler;

public class JTextAreaTester extends JFrame {

	public JTextAreaTester() {
		super("简易文本编辑器"); // 调用父类的构造方法
		// 创建菜单栏(JMenuBar)对象
		JMenuBar table = new JMenuBar();
		// 在JFrame等容器中设置菜单栏对象，即将菜单栏添加到框架容器中
		this.setJMenuBar(table);

		// 创建菜单
		JMenu file = new JMenu("文件");
		JMenu edit = new JMenu("编辑");
		JMenu form = new JMenu("格式");
		JMenu color = new JMenu("字体颜色");

		// 将菜单添加到菜单栏中
		table.add(file);
		table.add(edit);
		table.add(form);
		table.add(color);

		JTextArea workArea = new JTextArea(); // 创建多行文本框
		JScrollPane imgScrollPane = new JScrollPane(workArea); // 创建一个空视图，只要组件内容超过视图大小就会显示水平和垂直滚动条
		add(imgScrollPane, BorderLayout.CENTER); // 将当前类的对象实例加到frame的中间位置

		// 定义打开和保存对话框
		FileDialog openDia;
		FileDialog saveDia;
		// 默认模式为 FileDialog.LOAD
		openDia = new FileDialog(this, "打开", FileDialog.LOAD);
		saveDia = new FileDialog(this, "另存为", FileDialog.SAVE);

		JMenuItem item1_1 = new JMenuItem("新建"); // 生成一个对象
		item1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { // 对当前的控件添加监听器，点击控件时就会触发监听函数里面的内容
				workArea.setText(""); // 清空文本
			}
		});
		JMenuItem item1_2 = new JMenuItem("打开",new ImageIcon("C:\\Users\\Scott\\Desktop\\QQ截图20221107223520.png"));
		item1_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { // 对当前的控件添加监听器，点击控件时就会触发监听函数里面的内容
				openDia.setVisible(true); // 打开文件对话框
				String dirPath = openDia.getDirectory(); // 获取打开文件路径并保存
				String fileName = openDia.getFile(); // 获取文件名称并保存
				// 判断打开路径或目录是否为空，则返回空
				if (dirPath == null || fileName == null) {
					return;
				}
				workArea.setText("");// 清空文本
				File fileO = new File(dirPath, fileName);
				try {
					BufferedReader bufr = new BufferedReader(new FileReader(fileO)); // 尝试从文件中读取内容
					String line = null; // 变量字符串初始化为空
					while ((line = bufr.readLine()) != null) {
						workArea.append(line + "\r\n"); // 显示每行内容
					}
					bufr.close(); // 关闭文本
				} catch (IOException er1) {
					throw new RuntimeException("文件读取失败！");
				}
			}
		});

		JMenuItem item1_3 = new JMenuItem("保存");
		item1_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				File fileS = null;
				if (fileS == null) {
					saveDia.setVisible(true);
					String dirPath = saveDia.getDirectory();
					String fileName = saveDia.getFile();

					if (dirPath == null || fileName == null)
						return; // 返回空值

					fileS = new File(dirPath, fileName);
				}
				try {
					BufferedWriter bufw = new BufferedWriter(new FileWriter(fileS));
					String text = workArea.getText();
					bufw.write(text);
					bufw.close();
				} catch (IOException er) {
					throw new RuntimeException("文件保存失败！");
				}
			}
		});

		JMenuItem item1_4 = new JMenuItem("另存为");
		item1_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				File fileS = null;
				if (fileS == null) {
					saveDia.setVisible(true);
					String dirPath = saveDia.getDirectory();
					String fileName = saveDia.getFile();

					if (dirPath == null || fileName == null)
						return; // 返回空值
					fileS = new File(dirPath, fileName);
				}
				try {
					BufferedWriter bufw = new BufferedWriter(new FileWriter(fileS));
					String text = workArea.getText();
					bufw.write(text);
					bufw.close();
				} catch (IOException er) {
					throw new RuntimeException("文件保存失败！");
				}
			}
		});

		JMenuItem item1_5 = new JMenuItem("退出");
		item1_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});

		// 创建菜单项
		JMenuItem item2_1 = new JMenuItem("剪切");
		item2_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.cut();
			}
		});

		JMenuItem item2_2 = new JMenuItem("复制");
		item2_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.copy();
			}
		});

		JMenuItem item2_3 = new JMenuItem("粘贴");
		item2_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.paste();
			}
		});

		JRadioButtonMenuItem item3_1 = new JRadioButtonMenuItem("自动换行", false);
		item3_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { // 对当前的控件添加一个监听器，点击控件时就会触发监听函数里面的内容
				Object source = e.getSource();
				if (source == item3_1)
					workArea.setLineWrap(true); // 自动换行
				else if (source != item3_1)
					workArea.setLineWrap(false);
			}
		});
		JMenuItem item4_1 = new JMenuItem("蓝色");
		item4_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.BLUE);
			}
		});
		JMenuItem item4_2 = new JMenuItem("绿色");
		item4_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.green);
			}
		});
		JMenuItem item4_3 = new JMenuItem("红色");
		item4_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.RED);
			}
		});
		JMenuItem item4_4 = new JMenuItem("黑色");
		item4_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.BLACK);
			}
		});

		// 在菜单中添加菜单项
		file.add(item1_1);
		file.add(item1_2);
		file.add(item1_3);
		file.add(item1_4);
		file.add(item1_5);
		edit.add(item2_1);
		edit.add(item2_2);
		edit.add(item2_3);
		form.add(item3_1);
		color.add(item4_1);
		color.add(item4_2);
		color.add(item4_3);
		color.add(item4_4);

	}// 构造方法结束

	public static void main(String args[]) {
		JTextAreaTester app = new JTextAreaTester();

		app.setSize(600, 400); // 设置窗口大小,宽度600，高度400
		app.setLocation(200, 200); // 设置窗口位置为距离屏幕左边水平方向200，上方垂直方向200
		app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 点击关闭按钮是直接退出
		app.setVisible(true); // 设置窗体可见
	}
}
