package test19;

import java.io.FileInputStream;
import java.io.InputStream;

public class test19 {
    public static void main(String args[]) {
        byte[] array = new byte[1024];

        try {
            InputStream input = new FileInputStream("input.txt");

            System.out.println("文件中的可用字节：" + input.available());

            input.read(array);
            System.out.println("从文件读取的数据：");

            String data = new String(array);
            System.out.println(data);

            input.close();
        } catch (Exception e) {
            e.getStackTrace();
        }
    }
}
