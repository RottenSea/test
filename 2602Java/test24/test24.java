package test24;

public class test24 {

    public static void main(String[] args) {
        Bank bank = new Bank(1500);

        try {
            bank.withdrawal(2000);
            System.out.println("取款成功，余额：" + bank.getBalance());
        } catch (InsufficientFundsException e) {
            System.out.println(e.excepMessage());
        }

        try {
            bank.withdrawal(500);
        } catch (InsufficientFundsException e) {
            System.out.println(e.excepMessage());
        }
    }

}
