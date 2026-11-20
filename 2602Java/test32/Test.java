package test32;

public class Test {
    public static void main(String[] args) {
        Goods goods = new Goods(30);   // 初始库存 30

        // 3 个消费者
        Consumer c1 = new Consumer("消费者c1", 50, goods);
        Consumer c2 = new Consumer("消费者c2", 30, goods);
        Consumer c3 = new Consumer("消费者c3", 20, goods);

        // 7 个生产者:p1~p6 各 10,p7 为 80
        Producer p1 = new Producer("生产者p1", 10, goods);
        Producer p2 = new Producer("生产者p2", 10, goods);
        Producer p3 = new Producer("生产者p3", 10, goods);
        Producer p4 = new Producer("生产者p4", 10, goods);
        Producer p5 = new Producer("生产者p5", 10, goods);
        Producer p6 = new Producer("生产者p6", 10, goods);
        Producer p7 = new Producer("生产者p7", 80, goods);

        // 启动所有线程
        c1.start();
        c2.start();
        c3.start();
        p1.start();
        p2.start();
        p3.start();
        p4.start();
        p5.start();
        p6.start();
        p7.start();
    }
}
