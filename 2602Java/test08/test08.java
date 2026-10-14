package test08;

public class test08 {
    public static void main(String[] args) {
        Shape shape = new Circle();
        shape.showName();
        System.out.println(shape.getArea());

        shape = new Rectangle();
        shape.showName();
        System.out.println(shape.getArea());
    }
}