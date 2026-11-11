package test23;

import java.util.Scanner;

public class test23 {
    public static void divide() throws Exception {
        Scanner in = new Scanner(System.in);
        System.out.println("请输入被除数：");
        int a = in.nextInt();
        System.out.println("请输入除数：");
        int b = in.nextInt();

        System.out.println(String.format("%d / %d = %d", a, b, a / b));
    }

    public static void main(String[] args) {
        try {
            divide();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
    }
}