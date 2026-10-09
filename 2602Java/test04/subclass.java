package test04;

public class subclass extends superclass {

    @Override
    public void start() {
        System.out.println("子类启动");
    }

    @Override
    public void stop() {
        System.out.println("汽车停止");
    }
}
