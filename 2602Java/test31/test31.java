package test31;

public class test31 {
    public static void main(String[] args) {
        Demo d = new Demo();
        Thread t1 = new Thread(d);
        Thread t2 = new Thread(d);
        t1.start();
        t2.start();
        t2.setPriority(Thread.MAX_PRIORITY);
    }
}
