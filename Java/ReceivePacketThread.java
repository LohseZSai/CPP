package Java;

import java.io.*;
import java.net.*;
import javax.swing.*;
// 专门用于接收数据报的线程
public class ReceivePacketThread implements Runnable {
	private DatagramSocket socket;
	private JTextArea taRecvMsg;
	private byte[] rBuff=new byte[1024];// 接收消息的缓冲
	private DatagramPacket pack; // 用于接收数据的数据报
	public ReceivePacketThread(DatagramSocket socket, JTextArea taRecvMsg) {
		this.socket = socket;
		this.taRecvMsg = taRecvMsg;
    	pack=new DatagramPacket(rBuff, rBuff.length);// 创建用于接收数据的数据报
	}

	@Override
	public void run() {
		try {
			while(true)	receivePacket();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void receivePacket() throws IOException{ // 接收数据报的方法
    	// 创建用于接收数据的数据报
    	//DatagramPacket pack=new DatagramPacket(rBuff, rBuff.length);
    	socket.receive(pack); // 接收数据报
    	// 获取发送数据报的主机的IP地址、端口号
    	InetAddress IPAddr=pack.getAddress();
    	int port =pack.getPort();
    	// 从数据报中获取消息
    	String msg,line;
    	msg=new String(pack.getData(),pack.getOffset(),pack.getLength());
    	line="#来自IP"+IPAddr+":"+port+"的消息："+msg+"\n";
    	//System.out.println(line);
    	//taRecvMsg.append(line);
    	taRecvMsg.setText(line+taRecvMsg.getText());
    }

}
