package test10;

import java.util.LinkedList;
import java.util.Iterator;

public class link {
    public static void main(String[] args) {
        Student s1 = new Student("张三", 18);
        Student s2 = new Student("李四", 19);
        Student s3 = new Student("王五", 20);
        LinkedList<Student> l = new LinkedList<>();
        l.add(s1);
        l.add(s2);
        l.add(s3);

        Student s = l.getLast();

        System.out.println(s.getName() + " " + s.getAge());

        l.removeLast();
        Iterator<Student> it = l.iterator();

        while (it.hasNext()) {
            Student s6 = it.next();
            System.out.println(s6.getName() + " " + s6.getAge());
        }
    }
}
