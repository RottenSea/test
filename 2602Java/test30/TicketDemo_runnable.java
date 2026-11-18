package test30;

public class TicketDemo_runnable {

    public static void main(String[] args) {

        Ticket2 t = new Ticket2();
        Thread t1 = new Thread(t);
        Thread t2 = new Thread(t);
        Thread t3 = new Thread(t);
        Thread t4 = new Thread(t);

        t1.start();
        t2.start();
        t3.start();
        t4.start();

    }
}