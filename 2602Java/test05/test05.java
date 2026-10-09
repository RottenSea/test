import java.util.Arrays;

public class test05 {

    public static void main(String[] args) {
        int[] A = { 1, 8, 9, 13, 14, 6, 7, 8, 10, 15 };

        int[] B = Arrays.copyOf(A, A.length);

        Arrays.sort(B);

        int index = Arrays.binarySearch(B, 13);
        System.out.println("元素13在数组B中的下标: " + index);

        System.out.print("排序后数组B的全部元素: ");
        for (int num : B) {
            System.out.print(num + " ");
        }
        System.out.println();

        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < B.length; i++) {
            sb.append(B[i]);
            if (i < B.length - 1) {
                sb.append(",");
            }
        }
        String original = sb.toString();
        System.out.println("拼接字符串: " + original);

        StringBuffer reversed = sb.reverse();
        System.out.println("翻转字符串: " + reversed);

        System.out.println(
            "equals比较结果: " + reversed.toString().equals(original)
        );
    }
}
