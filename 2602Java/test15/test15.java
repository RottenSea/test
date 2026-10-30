package test15;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class test15 {

    public static void main(String[] args) {
        Map<String, String> students = new HashMap<>();

        students.put("20240101", "张三");
        students.put("20240102", "李四");
        students.put("20240103", "王五");
        students.put("20240104", "赵六");
        students.put("20240105", "孙七");
        System.out.println("① 已添加 " + students.size() + " 条学生信息");

        Scanner sc = new Scanner(System.in);
        System.out.print("请输入要查询的学号：");
        String id = sc.next();

        if (students.containsKey(id)) {
            System.out.println("② 学号 " + id + " 的学生姓名：" + students.get(id));
        } else {
            System.out.println("② 查无此学号：" + id);
        }

        System.out.println("③ 学号 20240102 是否存在：" + students.containsKey("20240102"));
        System.out.println("   学号 20240999 是否存在：" + students.containsKey("20240999"));

        System.out.println("④ 修改前，20240102 是：" + students.get("20240102"));
        students.put("20240102", "李小四");
        System.out.println("   修改后，20240102 是：" + students.get("20240102"));

        System.out.println("⑤ 删除 20240104，删掉的是：" + students.remove("20240104"));
        System.out.println("   还剩 " + students.size() + " 条记录");

        System.out.println("⑥ 迭代器遍历全部记录：");
        Iterator<Map.Entry<String, String>> it = students.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, String> entry = it.next();
            System.out.println("   学号：" + entry.getKey() + "，姓名：" + entry.getValue());
        }

        sc.close();
    }
}
