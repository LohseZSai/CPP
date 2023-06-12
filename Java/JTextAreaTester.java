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
		super("�����ı��༭��"); // ���ø���Ĺ��췽��
		// �����˵���(JMenuBar)����
		JMenuBar table = new JMenuBar();
		// ��JFrame�����������ò˵������󣬼����˵�����ӵ����������
		this.setJMenuBar(table);

		// �����˵�
		JMenu file = new JMenu("�ļ�");
		JMenu edit = new JMenu("�༭");
		JMenu form = new JMenu("��ʽ");
		JMenu color = new JMenu("������ɫ");

		// ���˵���ӵ��˵�����
		table.add(file);
		table.add(edit);
		table.add(form);
		table.add(color);

		JTextArea workArea = new JTextArea(); // ���������ı���
		JScrollPane imgScrollPane = new JScrollPane(workArea); // ����һ������ͼ��ֻҪ������ݳ�����ͼ��С�ͻ���ʾˮƽ�ʹ�ֱ������
		add(imgScrollPane, BorderLayout.CENTER); // ����ǰ��Ķ���ʵ���ӵ�frame���м�λ��

		// ����򿪺ͱ���Ի���
		FileDialog openDia;
		FileDialog saveDia;
		// Ĭ��ģʽΪ FileDialog.LOAD
		openDia = new FileDialog(this, "��", FileDialog.LOAD);
		saveDia = new FileDialog(this, "���Ϊ", FileDialog.SAVE);

		JMenuItem item1_1 = new JMenuItem("�½�"); // ����һ������
		item1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { // �Ե�ǰ�Ŀؼ���Ӽ�����������ؼ�ʱ�ͻᴥ�������������������
				workArea.setText(""); // ����ı�
			}
		});
		JMenuItem item1_2 = new JMenuItem("��",new ImageIcon("C:\\Users\\Scott\\Desktop\\QQ��ͼ20221107223520.png"));
		item1_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { // �Ե�ǰ�Ŀؼ���Ӽ�����������ؼ�ʱ�ͻᴥ�������������������
				openDia.setVisible(true); // ���ļ��Ի���
				String dirPath = openDia.getDirectory(); // ��ȡ���ļ�·��������
				String fileName = openDia.getFile(); // ��ȡ�ļ����Ʋ�����
				// �жϴ�·����Ŀ¼�Ƿ�Ϊ�գ��򷵻ؿ�
				if (dirPath == null || fileName == null) {
					return;
				}
				workArea.setText("");// ����ı�
				File fileO = new File(dirPath, fileName);
				try {
					BufferedReader bufr = new BufferedReader(new FileReader(fileO)); // ���Դ��ļ��ж�ȡ����
					String line = null; // �����ַ�����ʼ��Ϊ��
					while ((line = bufr.readLine()) != null) {
						workArea.append(line + "\r\n"); // ��ʾÿ������
					}
					bufr.close(); // �ر��ı�
				} catch (IOException er1) {
					throw new RuntimeException("�ļ���ȡʧ�ܣ�");
				}
			}
		});

		JMenuItem item1_3 = new JMenuItem("����");
		item1_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				File fileS = null;
				if (fileS == null) {
					saveDia.setVisible(true);
					String dirPath = saveDia.getDirectory();
					String fileName = saveDia.getFile();

					if (dirPath == null || fileName == null)
						return; // ���ؿ�ֵ

					fileS = new File(dirPath, fileName);
				}
				try {
					BufferedWriter bufw = new BufferedWriter(new FileWriter(fileS));
					String text = workArea.getText();
					bufw.write(text);
					bufw.close();
				} catch (IOException er) {
					throw new RuntimeException("�ļ�����ʧ�ܣ�");
				}
			}
		});

		JMenuItem item1_4 = new JMenuItem("���Ϊ");
		item1_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				File fileS = null;
				if (fileS == null) {
					saveDia.setVisible(true);
					String dirPath = saveDia.getDirectory();
					String fileName = saveDia.getFile();

					if (dirPath == null || fileName == null)
						return; // ���ؿ�ֵ
					fileS = new File(dirPath, fileName);
				}
				try {
					BufferedWriter bufw = new BufferedWriter(new FileWriter(fileS));
					String text = workArea.getText();
					bufw.write(text);
					bufw.close();
				} catch (IOException er) {
					throw new RuntimeException("�ļ�����ʧ�ܣ�");
				}
			}
		});

		JMenuItem item1_5 = new JMenuItem("�˳�");
		item1_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});

		// �����˵���
		JMenuItem item2_1 = new JMenuItem("����");
		item2_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.cut();
			}
		});

		JMenuItem item2_2 = new JMenuItem("����");
		item2_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.copy();
			}
		});

		JMenuItem item2_3 = new JMenuItem("ճ��");
		item2_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.paste();
			}
		});

		JRadioButtonMenuItem item3_1 = new JRadioButtonMenuItem("�Զ�����", false);
		item3_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) { // �Ե�ǰ�Ŀؼ����һ��������������ؼ�ʱ�ͻᴥ�������������������
				Object source = e.getSource();
				if (source == item3_1)
					workArea.setLineWrap(true); // �Զ�����
				else if (source != item3_1)
					workArea.setLineWrap(false);
			}
		});
		JMenuItem item4_1 = new JMenuItem("��ɫ");
		item4_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.BLUE);
			}
		});
		JMenuItem item4_2 = new JMenuItem("��ɫ");
		item4_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.green);
			}
		});
		JMenuItem item4_3 = new JMenuItem("��ɫ");
		item4_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.RED);
			}
		});
		JMenuItem item4_4 = new JMenuItem("��ɫ");
		item4_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				workArea.setForeground(Color.BLACK);
			}
		});

		// �ڲ˵�����Ӳ˵���
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

	}// ���췽������

	public static void main(String args[]) {
		JTextAreaTester app = new JTextAreaTester();

		app.setSize(600, 400); // ���ô��ڴ�С,���600���߶�400
		app.setLocation(200, 200); // ���ô���λ��Ϊ������Ļ���ˮƽ����200���Ϸ���ֱ����200
		app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // ����رհ�ť��ֱ���˳�
		app.setVisible(true); // ���ô���ɼ�
	}
}
