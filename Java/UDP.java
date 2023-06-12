package Java;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

public class UDP extends JFrame  implements ActionListener{
	// 成员变量
	private int localPort=1088;
	private int remotePort=1099;
	private String remoteIP="127.0.0.1";
	private DatagramSocket socket=null;
	//private byte[] rBuff=new byte[1024];// 接收消息的缓冲区
	
	// 界面中组件
	private JLabel lbl1,lbl2,lbl3,lbl4;
	private JTextField txtRemoteIP,txtRemotePort,txtLocalPort,txtSendMsg;
	private JButton btnSet,btnSend;
	private JTextArea taRecvMsg;
	private JPanel p1,p2,p3;
	private JScrollPane sp;
	
	public UDP(){ // 窗体构造方法 
		super("简单的UDP通信程序");
		try {
			String localIP=InetAddress.getLocalHost().getHostAddress();//127.0.0.1
			this.setTitle(getTitle()+"[本机IP="+localIP+"]");
			remoteIP=localIP; // 默认本机作为远程主机
		} catch (UnknownHostException e) {
			e.printStackTrace(); 
		}
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setSize(400, 400);
		
		p1=new JPanel(new FlowLayout(FlowLayout.LEFT));
		lbl1=new JLabel("远程IP：");
		lbl2=new JLabel("远程Port：");
		lbl3=new JLabel("本地Port：");
		txtRemoteIP=new JTextField(remoteIP,10);
		txtRemotePort=new JTextField(Integer.toString(remotePort),5);
		txtLocalPort=new JTextField(Integer.toString(localPort),5);
		btnSet=new JButton("设置");
		btnSet.setActionCommand("设置"); // 设置动作命令
		btnSet.addActionListener(this); // 添加动作事件监听器
		p1.add(lbl1);p1.add(txtRemoteIP);
		p1.add(lbl2);p1.add(txtRemotePort);
		p1.add(lbl3);p1.add(txtLocalPort);
		p1.add(btnSet);
		
		p2=new JPanel(new FlowLayout(FlowLayout.LEFT));
		lbl4=new JLabel("请输入信息：");
		txtSendMsg=new JTextField("",20);
		btnSend=new JButton("发送");
		btnSend.setActionCommand("发送"); // 设置动作命令
		btnSend.addActionListener(this); // 添加动作事件监听器
		btnSend.setEnabled(false);
		p2.add(lbl4);p2.add(txtSendMsg);
		p2.add(btnSend);
		
		p3=new JPanel(new GridLayout(2,1));
		p3.add(p1);p3.add(p2);
		
		taRecvMsg=new JTextArea(5,10);
		taRecvMsg.setFont(new Font("宋体",Font.BOLD,20));
		sp=new JScrollPane(taRecvMsg);	
		
		this.add(p3, "North");
		this.add(sp, "Center");
		this.pack();
	}
	public void setting(){ // 设置远程IP、端口号及本地端口号
		// 注意，如果IP远程IP地址（net-id,host-id）中host-id全部为1，则广播数据报到本网络（子网掩码，应在子网内）
		remoteIP=txtRemoteIP.getText().trim();
		remotePort=Integer.parseInt(txtRemotePort.getText().trim());
		localPort=Integer.parseInt(txtLocalPort.getText().trim());
		try {
			if(socket!=null) socket.close(); //如果之前创建了数据报Socket，则先关闭它
			socket=new DatagramSocket(localPort); // 创建数据报Socket
			JOptionPane.showMessageDialog(this, "设置成功", "提示", JOptionPane.INFORMATION_MESSAGE);
			btnSend.setEnabled(true);
		} catch (SocketException e1) {
			e1.printStackTrace();
		}
	}
	public void sendPacket (String msg){ // 发送数据报
		try {
			byte[] buff=msg.getBytes();
			// 创建用于发送数据的数据报
			DatagramPacket pack=new DatagramPacket(buff, buff.length, InetAddress.getByName(remoteIP), remotePort);
			socket.send(pack); // 发送数据报
			//System.out.println(pack.getAddress()+":"+pack.getPort());
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
       
   /* public void receivePacket() throws IOException{ // 接收数据报的方法
    	// 创建用于接收数据的数据报
    	DatagramPacket pack=new DatagramPacket(rBuff, rBuff.length);
    	socket.receive(pack);
    	InetAddress IPAddr=pack.getAddress();// 获取发送数据报的主机的IP地址
    	int port =pack.getPort(); //获取发送数据报的主机的端口号
    	String s=new String(pack.getData(),pack.getOffset(),pack.getLength());
    	String str="来自IP"+IPAddr+":"+port+"的消息："+s+"\n";
    	//System.out.println(str);
    	taRecvMsg.append(str);
    }*/
    
    @Override
	public void actionPerformed(ActionEvent e) {
		String cmd=e.getActionCommand();
		//System.out.println(cmd);
		if(cmd=="设置"){
			this.setting();
			//创建接收数据报的线程
			Thread receiveThead=new Thread(new ReceivePacketThread(socket, taRecvMsg));
			receiveThead.start();	
			//while(true)
			//	this.receivePacket();
		}else if(cmd=="发送"){
			String msg=txtSendMsg.getText();
			//txtSendMsg.setText(null);
			this.sendPacket(msg);
		}	
	}
    
	public static void main(String[] args) {
		UDP frm=new UDP();
		frm.setVisible(true);
	}	
}
