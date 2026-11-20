package test32;

public class Goods {
    private static final int MAX = 100;  // 仓库最大容量
    private int current;                 // 当前库存

    public Goods() {
        this.current = 0;
    }

    public Goods(int current) {
        this.current = current;
    }

    // 同步生产方法
    public synchronized void produce(int neednum) {
        while (current + neednum > MAX) {
            System.out.println("【超过库存，无法生产!】" + Thread.currentThread().getName()
                    + " 需要 " + neednum + ",当前库存 " + current + ",进入等待...");
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        current += neednum;
        System.out.println(Thread.currentThread().getName() + " 生产了 " + neednum
                + " 件产品,当前库存: " + current);
        notifyAll();
    }

    // 同步消费方法
    public synchronized void consume(int neednum) {
        while (current < neednum) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        current -= neednum;
        System.out.println(Thread.currentThread().getName() + " 消费了 " + neednum
                + " 件产品,当前库存: " + current);
        notifyAll();
    }
}
