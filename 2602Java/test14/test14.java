package test14;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class test14 {

    public static void main(String[] args) {
        // 学号是 String，姓名也是 String；HashMap 存“学号 -> 姓名”
        // 之后所有操作都靠学号（key）去动姓名（value），这正是 HashMap 擅长的
        Map<String, String> students = new HashMap<>();

        System.out.println("=== 1. 添加 5 条学生信息 ===");
        students.put("20240101", "张三");
        students.put("20240102", "李四");
        students.put("20240103", "王五");
        students.put("20240104", "赵六");
        students.put("20240105", "孙七");
        System.out.println("共 " + students.size() + " 条：" + students);
        System.out.println();

        System.out.println("=== 2. 按指定学号查询姓名 ===");
        // 要查的学号先放进变量，后面判断、修改、删除都能复用，改一处即可
        String id = "20240103";
        System.out.println("学号 " + id + " 对应：" + students.get(id));
        System.out.println();

        System.out.println("=== 3. 判断某学号是否存在 ===");
        // containsKey() 只认 key，返回 boolean；不怕学号不存在（get() 不存在会返回 null）
        System.out.println("学号 20240102 存在吗：" + students.containsKey("20240102"));
        System.out.println("学号 20240999 存在吗：" + students.containsKey("20240999"));
        System.out.println();

        System.out.println("=== 4. 按学号修改姓名 ===");
        // 键不变、再 put 一次就是覆盖旧值，所以“修改”不需要单独的方法
        System.out.println("修改前：" + students.get("20240102"));
        students.put("20240102", "李小四");
        System.out.println("修改后：" + students.get("20240102"));
        System.out.println();

        System.out.println("=== 5. 按学号删除一条记录 ===");
        // remove() 把删掉的那个 value 返回回来，可以用输出确认真删对了人
        System.out.println("删掉 20240104，是：" + students.remove("20240104"));
        System.out.println("删完还剩 " + students.size() + " 条：" + students);
        System.out.println();

        System.out.println("=== 6. 用迭代器遍历全部学号和姓名 ===");
        // 要同时拿到学号和姓名，就用 entrySet() 的迭代器：一个 entry 就是一个键值对
        Iterator<Map.Entry<String, String>> it = students.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, String> entry = it.next();
            System.out.println("学号：" + entry.getKey() + "  姓名：" + entry.getValue());
        }
    }

}
