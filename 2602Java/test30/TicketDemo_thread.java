package test30;

public class TicketDemo_thread extends Thread {
    private static int ticket = 100;

    public void run() {
        while (ticket > 0) {
            System.out.println(getName() + "正在卖第" + ticket + "张票");
            ticket--;
        }
    }

    public static void main(String[] args) {
        new TicketDemo_thread().start();
        new TicketDemo_thread().start();
        new TicketDemo_thread().start();
        new TicketDemo_thread().start();
    }
}
