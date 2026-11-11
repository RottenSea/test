package test25;

public class InsufficientFundsException extends Exception {
    private Bank excepbank;
    private double excepAmount;

    public InsufficientFundsException(Bank ba, double dAmount) {
        excepbank = ba;
        excepAmount = dAmount;
    }

    public String excepMessage() {
        String str = "The balance is  " + excepbank.getBalance() + "\n"
                + "The withdrawal was  " + excepAmount;
        return str;
    }
}
