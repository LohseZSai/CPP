package Java;

import java.io.*;

public class yesyes {
	// 主要是采用制表符和spilt方法的方式进行“漂亮打印”
	public static void main(String[] args) {
		String fileName = "C:\\Users\\Scott\\Documents\\Tencent Files\\1172720089\\FileRecv\\score.csv";
		try {
			BufferedReader df = new BufferedReader(
					new InputStreamReader(new FileInputStream(fileName), "UTF-8"));
			String line = df.readLine();
			System.out.println("id" + "\t" + "class" + "\t" + "\tno" + "\t" + "\tname" + "\t" + "score");
			int i = 0;
			while (line != null) {
				String[] content = line.split(",");
				System.out.println(
						i + "\t" + content[0] + "\t" + content[1] + "\t" + content[2] + "\t" + content[3] + "\t");
				i += 1;
				line = df.readLine();
			}

			df.close();

		} catch (IOException e) {
			System.out.println(e.getMessage());
		}

	}
}
