package test08;

public class test08 {
    public static void main(String[] args) {
        Shape shape = new Circle(2.0);
        shape.showName();
        System.out.println(shape.getArea());

        shape = new Rectangle(3.0, 4.0);
        shape.showName();
        System.out.println(shape.getArea());
    }
}