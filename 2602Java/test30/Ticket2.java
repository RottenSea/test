package test30;

public class Ticket2 implements Runnable {
    private int ticket = 100;

    public void run() {
        while (true) {
            synchronized (this) {
                if (ticket > 0) {
                    try {
                        System.out.println(Thread.currentThread().getName() + "正在卖第" + ticket + "张票");
                        ticket--;
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }
}
