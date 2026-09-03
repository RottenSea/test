import java.util.Scanner;

public class Test002 {

    public static void main(String[] args) {
        System.out.println("Input Season: ");
        Scanner scanner = new Scanner(System.in);
        String season = scanner.nextLine();
        switch (season) {
            case "Spring":
                System.out.println(
                    "Spring: blossoms bloom, weather turns warm and mild."
                );
                break;
            case "Summer":
                System.out.println(
                    "Summer: sunny and hot, the season of green shade and cicadas."
                );
                break;
            case "Fall":
                System.out.println(
                    "Fall: leaves turn golden, the air grows crisp and cool."
                );
                break;
            case "Winter":
                System.out.println(
                    "Winter: cold and quiet, a season of frost and snow."
                );
                break;
            default:
                System.out.println("Invalid season");
        }
    }
}
