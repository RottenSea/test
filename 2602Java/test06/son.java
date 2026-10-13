package test06;

public class son extends father{
    @Override
    void show() {
        System.out.println("子类show方法");
    }

    public static void main(String[] args){
        father f = new son();
        f.show();
        son s = (son)f;
        s.show();
    }
}
