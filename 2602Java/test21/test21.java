package test21;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class test21 {
    public static void main(String args[]) {

        String src = "a.jpg";
        String dest = "copy.jpg";

        try {
            InputStream input = new FileInputStream(src);
            OutputStream output = new FileOutputStream(dest);
            byte[] array = new byte[8192];

            int len;
            while ((len = input.read(array)) != -1) {
                output.write(array, 0, len);
            }
            input.close();
            output.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}