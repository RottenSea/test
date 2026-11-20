package test32;

public class Consumer extends Thread {
    private int neednum;   // 需要消费的数量
    private Goods goods;   // 仓库对象

    public Consumer(int neednum, Goods goods) {
        this.neednum = neednum;
        this.goods = goods;
    }

    public Consumer(String name, int neednum, Goods goods) {
        super(name);
        this.neednum = neednum;
        this.goods = goods;
    }

    @Override
    public void run() {
        goods.consume(neednum);
    }
}
