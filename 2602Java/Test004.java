public class Test004 {
    public static void main(String[] args) {
        int sum = 0;
        int i = 1;
        while (sum <= 2000) {
            sum += i;
            i++;
        }
        System.out.println("Count: " + (i-1));
    }
}
