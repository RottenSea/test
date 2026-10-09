package test04;

public class test04 {

    public void show() {
        System.out.println("无参数show()");
    }

    public void show(int a) {
        System.out.println("一个整数：" + a);
    }

    public void show(int a, int b) {
        System.out.println("两个整数：" + a + " 和 " + b);
    }

    public void show(double a) {
        System.out.println("一个浮点数：" + a);
    }

    public static void main(String[] args) {
        // test04 t = new test04();
        // t.show();
        // t.show(10);
        // t.show(10, 20);
        // t.show(3.14);

        subclass s = new subclass();
        s.start();
        s.stop();
        s.run();

        superclass superclass = new superclass();
        superclass.start();
        superclass.stop();
        superclass.run();
    }
}
