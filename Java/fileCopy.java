package Java;

import java.io.*;

public class fileCopy {
    public static boolean copy(String src, String test) {
        try {
            // �������������ֽ�������
            // ʹ��buffer�໺�壬����Ч��
            BufferedInputStream fis = new BufferedInputStream(new FileInputStream(src));
            BufferedOutputStream fos = new BufferedOutputStream(new FileOutputStream(test));
            System.out.println("���ڿ�����......");
            byte[] b = new byte[fis.available()];// �����ֽ����飬��СΪ�ļ�����
            fis.read(b);
            fos.write(b);
            fis.close();
            fos.close();
            System.out.println("�������");
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;

        }

    }

}