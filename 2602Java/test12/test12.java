package test12;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

public class test12 {

    public static void main(String[] args) {
        demoBasic();
        demoLoop();
        demoKeyAndNull();
        demoWordCount();
        demoTreemap();
        demoLinkedHashMap();
        demoObjectValue();
    }

    // 1. HashMap 常用方法：存、取、判、删、清
    private static void demoBasic() {
        System.out.println("=== 1. HashMap 常用方法 ===");

        // Map 存的是“键 -> 值”的配对，键好比数组的下标，只是下标可以是任意类型
        Map<String, String> students = new HashMap<>();
        students.put("20240101", "张三");
        students.put("20240102", "李四");
        students.put("20240103", "王五");
        students.put("20240104", "赵六");
        System.out.println("放进去 4 个人：" + students);
        System.out.println("size() = " + students.size());

        // get() 取不到时返回 null；getOrDefault() 直接给个默认值，省掉一次判空
        System.out.println("取 20240101：" + students.get("20240101"));
        System.out.println("取不存在的 20240999：" + students.get("20240999"));
        System.out.println("getOrDefault 兜底成“查无此人”：" + students.getOrDefault("20240999", "查无此人"));

        // containsKey() 按哈希定位，很快；containsValue() 只能把值挨个比一遍
        System.out.println("containsKey 20240102：" + students.containsKey("20240102"));
        System.out.println("containsValue 王五：" + students.containsValue("王五"));

        // remove() 返回被删掉的那个值；键本来就不在，返回 null
        System.out.println("remove 20240103 返回：" + students.remove("20240103"));
        System.out.println("再 remove 20240103：" + students.remove("20240103") + "（键已经没了）");
        System.out.println("剩 " + students.size() + " 个人：" + students);

        students.clear();
        System.out.println("clear() 之后 isEmpty()：" + students.isEmpty());
        System.out.println();
    }

    // 2. 四种遍历写法，按场景挑
    private static void demoLoop() {
        System.out.println("=== 2. 四种遍历方式 ===");
        Map<String, Integer> scores = new HashMap<>();
        scores.put("张三", 92);
        scores.put("李四", 85);
        scores.put("王五", 78);

        // ① keySet() + get()：只要键时最省事，代价是每个键都要再查一次值
        System.out.println("-- ① keySet() + get() --");
        for (String name : scores.keySet()) {
            System.out.println(name + " -> " + scores.get(name));
        }

        // ② values()：只关心值，不关心键
        System.out.println("-- ② values() --");
        int total = 0;
        for (int score : scores.values()) {
            total += score;
        }
        System.out.println("总分 " + total + "，平均 " + (total / scores.size()));

        // ③ entrySet() + Iterator：老写法，好处是遍历途中能用 it.remove() 安全地删元素
        System.out.println("-- ③ entrySet() + Iterator --");
        Iterator<Map.Entry<String, Integer>> it = scores.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, Integer> entry = it.next();
            System.out.println(entry.getKey() + " -> " + entry.getValue());
        }

        // ④ entrySet() + for-each：一趟同时拿到键和值，日常最常用
        System.out.println("-- ④ entrySet() + for-each --");
        for (Map.Entry<String, Integer> entry : scores.entrySet()) {
            if (entry.getValue() >= 85) {
                System.out.println(entry.getKey() + " 优秀：" + entry.getValue());
            }
        }
        System.out.println();
    }

    // 3. 键重复会覆盖；HashMap 允许 null 键和 null 值
    private static void demoKeyAndNull() {
        System.out.println("=== 3. 键重复与 null ===");
        Map<String, String> map = new HashMap<>();

        // 键相同就是覆盖。put() 的返回值是被覆盖掉的旧值，第一次放进去返回 null
        System.out.println("put a=张三 返回：" + map.put("a", "张三"));
        System.out.println("再 put a=王五 返回：" + map.put("a", "王五"));
        System.out.println("键不会变成两个，size = " + map.size() + "，a 已经是 " + map.get("a"));

        // replace() 只在键已存在时改值，返回值同样是旧值
        System.out.println("replace a=赵六 返回：" + map.replace("a", "赵六"));
        System.out.println("replace zzz 返回：" + map.replace("zzz", "新人") + "（键不存在，什么也没做）");

        map.put(null, "没有学号的同学");
        map.put("b", null);
        map.put("c", null);
        System.out.println("允许 1 个 null 键、多个 null 值：" + map);
        System.out.println();
    }

    // 4. 词频统计：Map 最经典的用法
    private static void demoWordCount() {
        System.out.println("=== 4. 词频统计 ===");
        String text = "读书 使人 明智 读书 使人 快乐 读书 吧";
        String[] words = text.split(" ");

        Map<String, Integer> count = new HashMap<>();
        for (String word : words) {
            // 没见过的词当 0 次，见过的在原来次数上加 1
            count.put(word, count.getOrDefault(word, 0) + 1);
        }
        System.out.println("原文：" + text);
        System.out.println("统计：" + count);

        // 顺手找出出现次数最多的那个词
        String hottest = null;
        int max = 0;
        for (Map.Entry<String, Integer> entry : count.entrySet()) {
            if (entry.getValue() > max) {
                max = entry.getValue();
                hottest = entry.getKey();
            }
        }
        System.out.println("最多的是「" + hottest + "」，出现 " + max + " 次");
        System.out.println();
    }

    // 5. TreeMap 按 key 排序，顺带对比 HashMap 的无序
    private static void demoTreemap() {
        System.out.println("=== 5. TreeMap：按 key 排序 ===");
        Map<String, String> hashMap = new HashMap<>();
        Map<String, String> treeMap = new TreeMap<>();
        String[] ids = { "20240103", "20240101", "20240104", "20240102" };
        String[] names = { "王五", "张三", "赵六", "李四" };
        for (int i = 0; i < ids.length; i++) {
            hashMap.put(ids[i], names[i]);
            treeMap.put(ids[i], names[i]);
        }

        System.out.println("插入顺序：20240103 20240101 20240104 20240102");
        System.out.println("HashMap：" + hashMap);
        System.out.println("TreeMap：" + treeMap + "  <- 按学号从小到大排好了");

        // TreeMap 靠比较 key 来排序，所以 key 不能是 null；HashMap 没有这个限制
        System.out.println();
    }

    // 6. LinkedHashMap：内部多一条链表，记住插入的先后
    private static void demoLinkedHashMap() {
        System.out.println("=== 6. LinkedHashMap：记住插入顺序 ===");
        Map<String, Integer> linked = new LinkedHashMap<>();
        linked.put("语文", 88);
        linked.put("数学", 95);
        linked.put("英语", 79);

        Map<String, Integer> hash = new HashMap<>();
        hash.put("语文", 88);
        hash.put("数学", 95);
        hash.put("英语", 79);

        System.out.println("插入顺序：语文 数学 英语");
        System.out.println("LinkedHashMap：" + linked + "  <- 和插入顺序一致");
        System.out.println("HashMap：" + hash + "  <- 按哈希值排，和插入顺序无关");
        System.out.println();
    }

    // 7. 值可以放自定义对象，键照样当“索引”用
    private static void demoObjectValue() {
        System.out.println("=== 7. Map 里放自定义对象 ===");
        Map<String, Student> students = new HashMap<>();
        students.put("20240101", new Student("张三", 18));
        students.put("20240102", new Student("李四", 19));
        students.put("20240103", new Student("王五", 20));

        for (Map.Entry<String, Student> entry : students.entrySet()) {
            System.out.println(entry.getKey() + " -> " + entry.getValue());
        }

        // 换掉整个对象要再 put 一次；只改对象自己的属性则不用 put
        students.put("20240101", new Student("张三", 20));
        System.out.println("重新 put 一个新对象：" + students.get("20240101"));
        students.get("20240102").setAge(21);
        System.out.println("直接改对象属性（没有再 put）：" + students.get("20240102"));
    }
}
