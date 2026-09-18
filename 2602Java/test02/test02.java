package test02;

import java.util.Scanner;

class Car {

    String brand;
    double price;

    static String factory = "长春汽车制造厂";
    static int carTotal = 0;

    public Car(Scanner scanner) {
        System.out.print("请输入汽车品牌：");
        this.brand = scanner.nextLine();

        System.out.print("请输入汽车价格：");
        this.price = scanner.nextDouble();

        carTotal++;
    }

    public static void showFactoryInfo() {
        System.out.println("制造厂：" + factory);
        System.out.println("汽车总数：" + carTotal);
    }
}

public class test02 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Car car1 = new Car(scanner);
        Car car2 = new Car(scanner);
        Car car3 = new Car(scanner);
        scanner.close();

        Car.showFactoryInfo();

        System.out.println(Car.factory);
    }
}
