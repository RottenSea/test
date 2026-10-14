package test07;

public class Rectangle extends Shape {

    double length;
    double width;

    Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
        this.name = "Rectangle";
    }

    @Override
    double getArea() {
        return length * width;
    }
}
