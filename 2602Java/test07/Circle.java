package test07;

public class Circle extends Shape {

    double radius;

    Circle(double radius) {
        this.radius = radius;
        this.name = "Circle";
    }

    @Override
    double getArea() {
        return Math.PI * radius * radius;
    }
}
