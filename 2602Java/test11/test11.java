package test11;

import java.util.Collection;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.Arrays;

public class test11 {
    private static <T> void printAll(Iterable<T> src) {
        Iterator<T> it = src.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }

    private static void printAll(double[] src) {
        for (double d : src) {
            System.out.println(d);
        }
    }

    public static void main(String[] args) {
        System.out.println("Hello World!");

        Collection<String> coll = new ArrayList<String>();
        coll.add("张三");
        coll.add("李四");
        coll.add(String.valueOf(123));

        Integer[] a = new Integer[] { 1, 2, 3, 4, 5 };
        String[] b = new String[] { "tony", "jack", "rose", "xiongda", "xiongder" };
        double[] c = new double[] { 1.1, 2.2, 3.3, 4.4, 5.5 };

        printAll(coll);
        printAll(Arrays.asList(a));
        printAll(Arrays.asList(b));
        printAll(c);
    }
}
