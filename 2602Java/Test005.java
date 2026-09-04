import java.util.Scanner;

public class Test005 {
    public static void main(String[] args) {
        String passwd = "123456";
        Scanner scanner = new Scanner(System.in);
        String input;

        do {
            System.out.print("Enter password: ");
            input = scanner.nextLine();

            if (input.equals(passwd)) {
                System.out.println("Login successful");
            } else {
                System.out.println("Login failed, please try again.");
            }
        } while (!input.equals(passwd));

        scanner.close();
    }
}
