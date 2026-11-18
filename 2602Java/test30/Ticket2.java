package test30;

public class Ticket2 implements Runnable {
    private int ticket = 100;

    public void run() {
        while (ticket > 0) {
            System.out.println(Thread.currentThread().getName() + "正在卖第" + ticket + "张票");
            ticket--;
        }
    }
}
