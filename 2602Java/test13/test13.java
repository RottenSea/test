package test13;

import java.util.LinkedHashMap;
import java.util.Map;

public class test13 {

    public static void main(String[] args) {
        Map<String, String> countries = new LinkedHashMap<>();
        countries.put("US", "美利坚合众国");
        countries.put("RU", "俄罗斯联邦");
        countries.put("CN", "中华人民共和国");
        countries.put("FR", "法兰西共和国");

        System.out.println("CN对应的国家是： " + countries.get("CN"));

        System.out.println("Map中共有" + countries.size() + "组数据");

        System.out.println("Map中包含FR的key吗? " + countries.containsKey("FR"));

        countries.remove("FR");
        System.out.println("Map中包含FR的key吗? " + countries.containsKey("FR"));

        System.out.println(countries.keySet());
        System.out.println(countries.values());
        System.out.println(countries);
    }
}
