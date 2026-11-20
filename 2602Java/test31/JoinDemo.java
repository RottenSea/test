package test31;

public class JoinDemo {
    public static void main(String[] args) throws Exception {
        Demo d = new Demo();
        Thread t1 = new Thread(d);
        Thread t2 = new Thread(d);
        t1.start();
        t2.start();
        t1.join();
        for (int i = 0; i < 100; i++) {
            System.out.println("main:" + i);
        }
        System.out.println("main end");

    }
}
