package Java;

import java.io.*;

public class fileCopy {
    public static boolean copy(String src, String test) {
        try {
            // 创建文字输入字节流对象
            // 使用buffer类缓冲，提升效率
            BufferedInputStream fis = new BufferedInputStream(new FileInputStream(src));
            BufferedOutputStream fos = new BufferedOutputStream(new FileOutputStream(test));
            System.out.println("正在拷贝中......");
            byte[] b = new byte[fis.available()];// 定义字节数组，大小为文件长度
            fis.read(b);
            fos.write(b);
            fis.close();
            fos.close();
            System.out.println("复制完成");
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;

        }

    }

}