package test25;

public class test25 {
    public static void main(String args[]) {
        Bank bank = new Bank(1000);

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
