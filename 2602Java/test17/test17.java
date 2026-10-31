package test17;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;

public class test17 {
    public static void main(String args[]) {
        try {
            FileReader fr = new FileReader("test.txt");
            FileWriter fw = new FileWriter("D:\\target.txt");
            char[] cbuf = new char[1024];
            int len;
            while ((len = fr.read(cbuf)) != -1) {
                fw.write(cbuf, 0, len);
            }
            fr.close();
            fw.close();
            System.out.println("复制完成，目标文件 " + new File("target.txt").length() + " 字节");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
