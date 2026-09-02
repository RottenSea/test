import java.util.Scanner;

public class Input {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter radius: ");
        double radius = input.nextDouble();

        double area = radius * radius * Math.PI;
        System.out.println(
            "The area for the circle of radius " + radius + " is " + area
        );

        input.close();
    }
}
