package test29;

public class RunnableDemo implements Runnable {
    public void run() {
        for (int i = 0; i < 20; i++) {
            System.out.println("Runnable:" + i);
        }
    }
}
