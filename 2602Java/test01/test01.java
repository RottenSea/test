package test01;

class Person{
    float height;
    float weight;
    String name;
}

class Rectangle {
    float width;
    float height;

    public Rectangle(float width, float height) {
        this.width = width;
        this.height = height;
    }

    public float getArea() {
        return width * height;
    }
}

public class test01 {
    public static void main(String[] args) {
        Rectangle rect = new Rectangle(10, 5);
        float area = rect.getArea();
        System.out.println("Area: " + area);
    }
}
