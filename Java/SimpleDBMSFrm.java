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
	SimpleDBMSFrm(){//构造方法
		super("碰到鬼了！！");
		this.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
		JPanel topPanel=new JPanel();
		topPanel.setLayout(new GridLayout(2,3));
		btvie=new JButton("显示");btque=new JButton("查询");
		btupd=new JButton("修改");btinc=new JButton("添加");
		btdel=new JButton("删除");btext=new JButton("退出");
		topPanel.add(btvie);topPanel.add(btque);
		topPanel.add(btupd);topPanel.add(btinc);
		topPanel.add(btdel);topPanel.add(btext);
		JPanel leftPanel=new JPanel();
		leftPanel.setLayout(new GridLayout(2,1));
		lb1=new JLabel("书名：");lb2=new JLabel("价格：");
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
		this.setResizable(false);//不允许改变窗体大小
		//添加事件监听器
		btvie.addActionListener(this);
		btque.addActionListener(this);
		btupd.addActionListener(this);
		btinc.addActionListener(this);
		btdel.addActionListener(this);
		btext.addActionListener(this);
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e)
			{//clearMemoryCloseWindowAndExit(e.getWindow());
				int option =JOptionPane.showConfirmDialog(null, "确定要退出应用吗","系统提示",JOptionPane.OK_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
				if(option!=JOptionPane.OK_OPTION)return;
//				wnd.dispose();//销毁window
				try{
					stmt.close();//关闭Statement对象
					con.close();//关闭数据库连接
				}catch(Exception e1){System.out.println(e1.toString());}
				System.exit(0);	
			}
		});
		//加载数据库驱动程序。建立连接。创建Statement对象

		try {
			Class.forName("com.hxtt.sql.access.AccessDriver");
			String url = "jdbc:Access/:C:/Users/Scott/Documents/Tencent Files/1172720089/FileRecv/BookPrice.accdb";
			con = DriverManager.getConnection(url, "", "");
			stmt = con.createStatement();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

	}
		//关闭窗体的确认及数据库资源的释放
//		public void clearMemoryCloseWindowAndExid(Window wnd){
//			//参数：wnd——要关闭的窗体
//			int option =JOptionPane.showConfirmDialog(wnd, "确定要退出应用吗","系统提示",JOptionPane.OK_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
//			if(option!=JOptionPane.OK_OPTION)return;
//			wnd.dispose();//销毁window
//			try{
//				stmt.close();//关闭Statement对象
//				con.close();//关闭数据库连接
//			}catch(Exception e){System.out.println(e.toString());}
//			System.exit(0);
//		}
	
		
		public void actionPerformed(ActionEvent e){//按钮动作事件处理程序
			if(e.getSource()==btvie){
				//显示
				try{
					String sql="SELECT BookName,Price FROM BookInf";
					rs=stmt.executeQuery(sql);
					ta.setText("书名\t\t\t价格(RMB)");
					while(rs.next()){
						nm=rs.getString("BookName");
						prc=rs.getFloat("Price");
						String s=String.format("%1$s\t\t\t%2$.2f",nm,prc);
						ta.append(s+"\n");
					}rs.close();
				}catch(Exception e1){System.out.println(e1.getMessage());}
			}		
			else if(e.getSource()==btque){//查询
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
					if(rec==0) tfld2.setText("数据库中没有这本书");
					rs.close();
				}catch(Exception e2){}
			}
			else if (e.getSource()==btupd){//修改
				try{
					str1=tfld1.getText().trim();str2=tfld2.getText().trim();
					String strUpd="UPDATE BookInf SET Price='"+str2+"'WHERE BookName='"+str1+"'";
					stmt.executeUpdate(strUpd);
			
				}catch(Exception e3){System.out.println(e3.toString());}
			}
			else if(e.getSource()==btinc){
				//添加
				try{
					str1=tfld1.getText().trim();str2=tfld2.getText().trim();
					String strInc="INSERT INTO Booklnf(BookName,Price)Values('"+str1+"','"+str2+"')";
					stmt.executeUpdate(strInc);
					JOptionPane.showMessageDialog(this, "添加完成!","好消息",JOptionPane.INFORMATION_MESSAGE);			
				}catch(Exception e4){System.out.println(e4.toString());
				JOptionPane.showMessageDialog(this, "添加失败!","坏消息",JOptionPane.ERROR_MESSAGE);}
			}
			else if(e.getSource()==btdel){
				//删除
				str1=tfld1.getText().trim();
				if(!str1.isEmpty()){
					int option=JOptionPane.showConfirmDialog(this,"确认要删除该记录吗？","系统提示",JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
					if(option==JOptionPane.YES_NO_CANCEL_OPTION){
						try{
							String strDel="DELETE FROM BookInf WHERE BookName='"+str1+"'";
							stmt.executeUpdate(strDel);
						}catch(Exception e5){
							System.out.println(e5.toString());
							JOptionPane.showMessageDialog(this,"删除失败","坏消息",JOptionPane.ERROR_MESSAGE);
						}
					}
				}
			}
			else if(e.getSource()==btext){
				//退出
				int option =JOptionPane.showConfirmDialog(null, "确定要退出应用吗","系统提示",JOptionPane.OK_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
				if(option!=JOptionPane.OK_OPTION)return;
//				wnd.dispose();//销毁window
				try{
					stmt.close();//关闭Statement对象
					con.close();//关闭数据库连接
				}catch(Exception e1){System.out.println(e1.toString());}
				System.exit(0);	
			}
		}
		
	

	

	public static void main(String[]args){
		SimpleDBMSFrm frm=new SimpleDBMSFrm();
		frm.setVisible(true);
		
}
}



