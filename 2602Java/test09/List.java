package test09;

import java.util.ArrayList;

public class List {
    public static void main(String[] args) {
        Student s1 = new Student(18, "张三");
        Student s2 = new Student(19, "李四");
        Student s3 = new Student(20, "王五");
        Student s4 = new Student(21, "赵六");
        Student s5 = new Student(22, "孙七");
        ArrayList<Student> list = new ArrayList<>();
        list.add(s1);
        list.add(s2);
        list.add(s3);
        list.add(s4);
        list.add(s5);

        for (Student s : list) {
            System.out.println(s);
        }
    }
}