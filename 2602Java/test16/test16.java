package test16;

import java.io.FileWriter;
import java.io.IOException;

public class test16 {
    public static void main(String[] args) {
        FileWriter fw = null;
        try {
            fw = new FileWriter("");
            fw.write("text");
        } catch (IOException e) {
            System.out.println("chuwentile");
            System.out.println(e.toString());
        } finally {
            if (fw != null) {
                try {
                    fw.close();
                } catch (IOException e) {
                    System.out.println(e.toString());
                }
            }
        }
    }
}
