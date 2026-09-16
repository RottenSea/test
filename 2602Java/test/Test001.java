import java.util.Scanner;

public class Test001 {

    public static void main(String[] args) {
        System.out.println("Please input a score, end with Q");
        Scanner scanner = new Scanner(System.in);
        while (true) {
            String input = scanner.nextLine();
            if (input.equals("Q")) {
                break;
            }
            int score = Integer.parseInt(input);
            if (score > 90) {
                System.out.println("A");
            } else if (score > 80) {
                System.out.println("B");
            } else if (score > 70) {
                System.out.println("C");
            } else if (score > 60) {
                System.out.println("D");
            } else {
                System.out.println("F");
            }

            System.out.println("Score: " + score);
        }
    }
}
