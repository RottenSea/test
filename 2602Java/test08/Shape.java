package test08;

public abstract class Shape {
    String name;

    public abstract double getArea();

    public void showName() {
        System.out.println("图形是" + name);
    }
}
