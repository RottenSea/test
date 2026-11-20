package test31;

public class Demo implements Runnable {
    public void run() {
        for (int i = 0; i < 80; i++) {
            System.out.println("线程" + Thread.currentThread().getName() + "正在运行" + i);
        }
    }
}
