package test29;

public class test29 {
    public static void main(String[] args) {
        // ThreadDemo t = new ThreadDemo();
        // t.start();
        // for (int i = 0; i < 1000; i++) {
        // System.out.println("main thread");
        // }

        RunnableDemo runner = new RunnableDemo();
        Thread t = new Thread(runner);
        t.start();
        for (int i = 0; i < 20; i++) {
            System.out.println("main thread" + i);
        }
    }
}
