package test08;

public class Circle extends Shape {

    double radius;

    Circle(double radius) {
        this.radius = radius;
        this.name = "Circle";
    }

    @Overrider
    public double getArea() {
        return Math.PI * radius * radius;
    }
}
