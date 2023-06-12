package Java;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.sql.*;
class SimpleDBMSFrm extends JFrame implements ActionListener {
	Connection con;
	Statement stmt;
	ResultSet rs;
	
	JButton btque,btupd,btinc,btdel,btvie,btext;
	JLabel lb1,lb2;
	JTextField tfld1,tfld2;
	JTextArea ta;
	String nm;
	float prc;
	String str1,str2;
	SimpleDBMSFrm(){//���췽��
		super("�������ˣ���");
		this.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
		JPanel topPanel=new JPanel();
		topPanel.setLayout(new GridLayout(2,3));
		btvie=new JButton("��ʾ");btque=new JButton("��ѯ");
		btupd=new JButton("�޸�");btinc=new JButton("���");
		btdel=new JButton("ɾ��");btext=new JButton("�˳�");
		topPanel.add(btvie);topPanel.add(btque);
		topPanel.add(btupd);topPanel.add(btinc);
		topPanel.add(btdel);topPanel.add(btext);
		JPanel leftPanel=new JPanel();
		leftPanel.setLayout(new GridLayout(2,1));
		lb1=new JLabel("������");lb2=new JLabel("�۸�");
		leftPanel.add(lb1);leftPanel.add(lb2);
		JPanel centerPanel=new JPanel();
		centerPanel.setLayout(new GridLayout(2,1));
		tfld1=new JTextField(15);tfld2=new JTextField(15);
		centerPanel.add(tfld1);centerPanel.add(tfld2);
		ta=new JTextArea(10,30);
		JScrollPane sp=new JScrollPane(ta);
		this.add(topPanel,"North");
		this.add(leftPanel,"West");
		this.add(centerPanel,"Center");
		this.add(sp,"South");
		this.pack();
		this.setResizable(false);//������ı䴰���С
		//����¼�������
		btvie.addActionListener(this);
		btque.addActionListener(this);
		btupd.addActionListener(this);
		btinc.addActionListener(this);
		btdel.addActionListener(this);
		btext.addActionListener(this);
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e)
			{//clearMemoryCloseWindowAndExit(e.getWindow());
				int option =JOptionPane.showConfirmDialog(null, "ȷ��Ҫ�˳�Ӧ����","ϵͳ��ʾ",JOptionPane.OK_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
				if(option!=JOptionPane.OK_OPTION)return;
//				wnd.dispose();//����window
				try{
					stmt.close();//�ر�Statement����
					con.close();//�ر����ݿ�����
				}catch(Exception e1){System.out.println(e1.toString());}
				System.exit(0);	
			}
		});
		//�������ݿ��������򡣽������ӡ�����Statement����

		try {
			Class.forName("com.hxtt.sql.access.AccessDriver");
			String url = "jdbc:Access/:C:/Users/Scott/Documents/Tencent Files/1172720089/FileRecv/BookPrice.accdb";
			con = DriverManager.getConnection(url, "", "");
			stmt = con.createStatement();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

	}
		//�رմ����ȷ�ϼ����ݿ���Դ���ͷ�
//		public void clearMemoryCloseWindowAndExid(Window wnd){
//			//������wnd����Ҫ�رյĴ���
//			int option =JOptionPane.showConfirmDialog(wnd, "ȷ��Ҫ�˳�Ӧ����","ϵͳ��ʾ",JOptionPane.OK_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
//			if(option!=JOptionPane.OK_OPTION)return;
//			wnd.dispose();//����window
//			try{
//				stmt.close();//�ر�Statement����
//				con.close();//�ر����ݿ�����
//			}catch(Exception e){System.out.println(e.toString());}
//			System.exit(0);
//		}
	
		
		public void actionPerformed(ActionEvent e){//��ť�����¼��������
			if(e.getSource()==btvie){
				//��ʾ
				try{
					String sql="SELECT BookName,Price FROM BookInf";
					rs=stmt.executeQuery(sql);
					ta.setText("����\t\t\t�۸�(RMB)");
					while(rs.next()){
						nm=rs.getString("BookName");
						prc=rs.getFloat("Price");
						String s=String.format("%1$s\t\t\t%2$.2f",nm,prc);
						ta.append(s+"\n");
					}rs.close();
				}catch(Exception e1){System.out.println(e1.getMessage());}
			}		
			else if(e.getSource()==btque){//��ѯ
				try{
					int rec=0;
					String sql="SELECT BookName,Price FROM BookINF";
					rs=stmt.executeQuery(sql);
					while(rs.next()){
						nm=rs.getString("BookName");
						prc=rs.getFloat("price");
						if(nm.equals(tfld1.getText().trim())){
							tfld2.setText(String.format("RMB%1$.2f",prc));
							rec=1;
							break;
						}
					}
					if(rec==0) tfld2.setText("���ݿ���û���Ȿ��");
					rs.close();
				}catch(Exception e2){}
			}
			else if (e.getSource()==btupd){//�޸�
				try{
					str1=tfld1.getText().trim();str2=tfld2.getText().trim();
					String strUpd="UPDATE BookInf SET Price='"+str2+"'WHERE BookName='"+str1+"'";
					stmt.executeUpdate(strUpd);
			
				}catch(Exception e3){System.out.println(e3.toString());}
			}
			else if(e.getSource()==btinc){
				//���
				try{
					str1=tfld1.getText().trim();str2=tfld2.getText().trim();
					String strInc="INSERT INTO Booklnf(BookName,Price)Values('"+str1+"','"+str2+"')";
					stmt.executeUpdate(strInc);
					JOptionPane.showMessageDialog(this, "������!","����Ϣ",JOptionPane.INFORMATION_MESSAGE);			
				}catch(Exception e4){System.out.println(e4.toString());
				JOptionPane.showMessageDialog(this, "���ʧ��!","����Ϣ",JOptionPane.ERROR_MESSAGE);}
			}
			else if(e.getSource()==btdel){
				//ɾ��
				str1=tfld1.getText().trim();
				if(!str1.isEmpty()){
					int option=JOptionPane.showConfirmDialog(this,"ȷ��Ҫɾ���ü�¼��","ϵͳ��ʾ",JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
					if(option==JOptionPane.YES_NO_CANCEL_OPTION){
						try{
							String strDel="DELETE FROM BookInf WHERE BookName='"+str1+"'";
							stmt.executeUpdate(strDel);
						}catch(Exception e5){
							System.out.println(e5.toString());
							JOptionPane.showMessageDialog(this,"ɾ��ʧ��","����Ϣ",JOptionPane.ERROR_MESSAGE);
						}
					}
				}
			}
			else if(e.getSource()==btext){
				//�˳�
				int option =JOptionPane.showConfirmDialog(null, "ȷ��Ҫ�˳�Ӧ����","ϵͳ��ʾ",JOptionPane.OK_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
				if(option!=JOptionPane.OK_OPTION)return;
//				wnd.dispose();//����window
				try{
					stmt.close();//�ر�Statement����
					con.close();//�ر����ݿ�����
				}catch(Exception e1){System.out.println(e1.toString());}
				System.exit(0);	
			}
		}
		
	

	

	public static void main(String[]args){
		SimpleDBMSFrm frm=new SimpleDBMSFrm();
		frm.setVisible(true);
		
}
}



