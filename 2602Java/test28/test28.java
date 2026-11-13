package test28;

import java.util.ArrayList;
import java.util.List;

public class test28 {
    public static void main(String[] args) {
        List<Student> students = new ArrayList<>();
        students.add(new Student("张三", 18, 85.5));
        students.add(new Student("李四", 19, 72.0));
        students.add(new Student("张五", 20, 91.0));
        students.add(new Student("王六", 18, 66.5));
        students.add(new Student("张七", 21, 78.5));

        System.out.println("学生名单（共 " + students.size() + " 人）：");
        for (Student s : students) {
            System.out.println("  " + s);
        }

        double sum = 0;
        int count = 0;
        for (Student s : students) {
            if (s.getName().startsWith("张")) {
                sum += s.getScore();
                count++;
            }
        }

        if (count == 0) {
            System.out.println("没有姓张的同学，无法计算平均成绩");
        } else {
            System.out.printf("姓张的同学共 %d 人，平均成绩为 %.2f%n", count, sum / count);
        }
    }
}
