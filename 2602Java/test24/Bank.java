package test24;

public class Bank {
    private double balance;

    public Bank() {
        this(0);
    }

    public Bank(double balance) {
        this.balance = balance;
    }

    public double getBalance() {
        return balance;
    }

    public void withdrawal(double amount) throws InsufficientFundsException {
        if (amount > balance) {
            throw new InsufficientFundsException(this, amount);
        }
        balance -= amount;
        System.out.println(String.format("取款 %.2f 成功，余额 %.2f", amount, balance));
    }
}
