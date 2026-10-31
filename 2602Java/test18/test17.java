package test18;

import java.io.*;

public class test17 {
    public static void main(String args[]) {
        FileWriter fw = null;
        BufferedWriter bw = null;
        try {
            fw = new FileWriter("C:\\Users\\RottenTh\\Desktop\\test.txt");
            bw = new BufferedWriter(fw);
            for (int x = 1; x < 5; x++) {
                bw.write(x + " ");
                bw.newLine();
                bw.flush();
            }
        } catch (Exception e) {
            System.out.println("chuwentile");
            System.out.println(e.toString());
        } finally {
            try {
                if (fw != null)
                    fw.close();
            } catch (Exception e) {
                System.out.println(e.toString());

            }
        }
    }
}