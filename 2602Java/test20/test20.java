package test20;

import java.io.FileOutputStream;

public class test20 {
    public static void main(String args[]) {
        String data = "这是文件中的一行文本。";

        try {
            FileOutputStream output = new FileOutputStream("output.txt");

            byte[] array = data.getBytes();

            output.write(array);

            output.close();

        } catch (Exception e) {
            e.getStackTrace();
        }
    }
}
