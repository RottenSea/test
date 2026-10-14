package test07;

public class test07 {

    public static void main(String[] args) {
        Shape c = new Circle(2);
        Shape r = new Rectangle(3, 4);

        c.showName();
        System.out.println("面积：" + c.getArea());

        r.showName();
        System.out.println("面积：" + r.getArea());
    }
}
