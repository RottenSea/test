package test07;

public abstract class Shape {

    String name;

    abstract double getArea();

    void showName() {
        System.out.println("图形名称：" + name);
    }
}
