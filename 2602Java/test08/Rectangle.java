package test08;

public class Rectangle extends Shape {

    double length;
    double width;

    Rectangle(double length, double width) {
        this.name = "Rectangle";
        this.length = length;
        this.width = width;
    }

    @Override
    public double getArea() {
        return width * width;
    }
}
