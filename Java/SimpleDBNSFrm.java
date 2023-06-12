package Java;

import java.awt.*;
import java.awt.event.*;
import java.sql.*;

import javax.swing.*;

public class SimpleDBNSFrm extends JFrame implements ActionListener {
	Connection con;
	Statement stmt;
	ResultSet rs;
	JButton btque, btupd, btinc, btdel, btvie, btext;
	JLabel lb1, lb2;
	JTextField tfld1, tfld2;
	JTextArea ta;
	String nm;
	float prc;
	String str1, str2;

	SimpleDBNSFrm() {
		super("�򵥵����ݹ���ϵͳ");
		this.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
		JPanel topPanel = new JPanel();
		topPanel.setLayout(new GridLayout(2, 3));
		btvie = new JButton("��ʾ");
		btque = new JButton("��ѯ");
		btupd = new JButton("�޸�");
		btdel = new JButton("ɾ��");
		btext = new JButton("�˳�");
		btinc = new JButton("���");
		JPanel leftPanel = new JPanel();
		leftPanel.setLayout(new GridLayout(2, 1));
		lb1 = new JLabel("������");
		lb2 = new JLabel("�۸�");
		leftPanel.add(lb1);
		leftPanel.add(lb2);
		JPanel centerPanel = new JPanel();
		centerPanel.setLayout(new GridLayout(2, 1));
		tfld1 = new JTextField(15);
		tfld2 = new JTextField(15);
		centerPanel.add(tfld1);
		centerPanel.add(tfld2);
		ta = new JTextArea(10, 30);
		JScrollPane sp = new JScrollPane(ta);
		this.add(topPanel, "North");
		this.add(leftPanel, "Wes");
		this.add(centerPanel, "Center");
		this.add(sp, "South");
		this.pack();
		this.setResizable(false);
		btque.addActionListener(this);
		btupd.addActionListener(this);
		btinc.addActionListener(this);
		btdel.addActionListener(this);
		btvie.addActionListener(this);
		btext.addActionListener(this);
		this.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				clearMemoryCloseWidowAndExit(e.getWindow());
			}
		});
		try {
			Class.forName("com.hxtt.sql.access.AccessDriver");//
			String url = "jdbc:Access:/C:/Users/zhang'zhi'kang/Desktop/BookPrice.accdb";
			con = DriverManager.getConnection(url, "", "");
			stmt = con.createStatement();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

	void clearMemoryCloseWidowAndExit(Window wnd) {
		int option = JOptionPane.showConfirmDialog(wnd, "ȷ��Ҫ�˳�Ӧ����?", "ϵͳ��ʾ", JOptionPane.OK_CANCEL_OPTION,
				JOptionPane.QUESTION_MESSAGE);
		if (option != JOptionPane.OK_OPTION)
			return;
		wnd.dispose();
		try {
			stmt.close();
			con.close();
		} catch (Exception e) {
			System.out.println(e.toString());
		}
		System.exit(0);
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == btvie) {
			try {
				String sql = "SELECT BookName,Price FROM BookInf";
				rs = stmt.executeQuery(sql);
				ta.setText("����\t\t\t�۸�(RMB)");
				while (rs.next()) {
					nm = rs.getString("BookName");
					prc = rs.getFloat("Price");
					String s = String.format("%1$s\t\t\t%2$.2f", nm, prc);
					ta.append(s + "\n");
				}
				rs.close();
			} catch (Exception e1) {
				System.out.println(e1.getMessage());
			}
		} else if (e.getSource() == btque) {
			try {
				int rec = 0;
				String sql = "SELECT BookName,Price FROM BookInf";
				rs = stmt.executeQuery(sql);
				while (rs.next()) {
					nm = rs.getString("BookName");
					prc = rs.getFloat("Price");
					if (nm.equals(tfld1.getText().trim())) {
						tfld2.setText(String.format("RMB%1$.2f", prc));
						rec = 1;
						break;
					}
				}
				if (rec == 0)
					tfld2.setText("���ݿ���û���Ȿ��");
				rs.close();
			} catch (Exception e2) {
			}
		} else if (e.getSource() == btupd) {
			// �޸�
			try {
				str1 = tfld1.getText().trim();
				str2 = tfld2.getText().trim();
				String strUpd = "UPDATE Booklnf SET Price='" + str2 + "'WHERE BookName = '" + str1 + "'";
			} catch (Exception e3) {
				System.out.println(e3.toString());
			}

		} else if (e.getSource() == btinc) {
			try {
				str1 = tfld1.getText().trim();
				str2 = tfld2.getText().trim();
				String strlnc = "INSERT INTO Booklnf(BookName,Price)Values('" + str1 + "','" + str2 + "')";
				stmt.executeUpdate(strlnc);
				JOptionPane.showMessageDialog(this, "�����ɣ�", "����Ϣ", JOptionPane.INFORMATION_MESSAGE);
			} catch (Exception e4) {
				System.out.println(e4.toString());
				JOptionPane.showMessageDialog(this, "���ʧ��", "����Ϣ��", JOptionPane.ERROR_MESSAGE);
			}
		} else if (e.getSource() == btdel) {
			str1 = tfld1.getText().trim();
			if (!str1.isEmpty()) {
				int option = JOptionPane.showConfirmDialog(this, "ȷ��Ҫɾ����¼��", "ϵͳ��ʾ", JOptionPane.YES_NO_CANCEL_OPTION,
						JOptionPane.QUESTION_MESSAGE);
				if (option == JOptionPane.YES_OPTION) {
					try {
						String strDel = "DELECT FROM Booklnf WHERE BookName='" + str1 + "'";
						stmt.executeUpdate(strDel);
					} catch (Exception e5) {
						e5.toString();
						JOptionPane.showMessageDialog(this, "ɾ��ʧ��", "����Ϣ��", JOptionPane.ERROR_MESSAGE);
					}
				}
			}
		} else if (e.getSource() == btext) {
			// �˳�
			clearMemoryCloseWidowAndExit(this);
		}
	}

}

