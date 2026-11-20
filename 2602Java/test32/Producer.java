package test32;

public class Producer extends Thread {
    private int neednum;   // 需要生产的数量
    private Goods goods;   // 仓库对象

    public Producer(int neednum, Goods goods) {
        this.neednum = neednum;
        this.goods = goods;
    }

    public Producer(String name, int neednum, Goods goods) {
        super(name);
        this.neednum = neednum;
        this.goods = goods;
    }

    @Override
    public void run() {
        goods.produce(neednum);
    }
}
