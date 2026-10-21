package test10;

import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class test10 {
    public static void main(String[] args) {
        Student s1 = new Student("张三", 18);
        List<Student> list = new ArrayList<>();
        list.add(s1);

        System.out.println("使用Iterator遍历，所有学生信息如下：");

        Iterator<Student> iterator = list.iterator();

        while (iterator.hasNext()) {
            Student s = iterator.next();
            System.out.println(s.getName() + " " + s.getAge());
        }
    }
}