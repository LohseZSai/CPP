package Java;
import java.io.*;
import java.net.*;
import java.nio.charset.Charset;
public class DownloadFileByURL{
    public static void main(String[] args) throws Exception{
        URL url;
        url = new URL("http://www.upc.edu.cn");
        InputStream in  = url.openStream();
        InputStreamReader isr = new InputStreamReader(in,Charset.forName("UTF-8"));
        BufferedReader br = new BufferedReader(isr);
        String line;
        while ((line=br.readLine()) != null)
        {System.out.println(line);}
        br.close();
    }
}

