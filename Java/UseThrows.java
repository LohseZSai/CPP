package Java;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class UseThrows {
	public static void main(String[] args) throws FileNotFoundException,IOException{
		throwExeption();
	}
	static void throwExeption() throws FileNotFoundException,IOException{
		int segmentLen = 1024;
		int m = 0;
		int fileSize = 0;
		byte[]b = new byte[segmentLen];
		
		FileInputStream fis = new FileInputStream("C:\\Users\\Scott\\Desktop\\dalabengba.txt");
		m = fis.read(b);
		while(m>0){
			fileSize += m;
			m = fis.read(b);
		}
			fis.close();
			System.out.println("文件大小为："+fileSize+"字节");
	}

}
