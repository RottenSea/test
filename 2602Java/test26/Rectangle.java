package test26;

public class Rectangle implements ShapeCalc {
    private double length;
    private double width;

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }

    @Override
    public double getArea() {
        return length * width;
    }

    @Override
    public double getPerimeter() {
        return 2 * (length + width);
    }

    @Override
    public String toString() {
        return String.format("length=%.1f, width=%.1f, perimeter=%.2f, area=%.2f",
                length, width, getPerimeter(), getArea());
    }
}
