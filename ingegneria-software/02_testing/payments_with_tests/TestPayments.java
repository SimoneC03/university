
/*
 * This file contains some test cases for the Payments class.
 * Every class method should be tested.
 */
import java.io.IOException;

public class TestPayments {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";

    private Payments p = new Payments();

    private void initAmounts() {
        p.drop();
        p.insertAmount(10);
        p.insertAmount(321.01f);
    }

    public void testCalcTotal() {
        initAmounts();
        p.calcTotal();
        if (p.getTotal() == 331.01f)
            System.out.println("test " + ANSI_GREEN + "OK" + ANSI_RESET + " - calculate total");
        else
            System.out.println("test " + ANSI_RED + "FAILED" + ANSI_RESET + " - calculate total");
    }

    public void testCalcMaxValue() {
        initAmounts();
        p.calcMaxValue();
        if (p.getMaxValue() == 321.01f)
            System.out.println("test " + ANSI_GREEN + "OK" + ANSI_RESET + " - calculate max value");
        else
            System.out.println("test " + ANSI_RED + "FAILED" + ANSI_RESET + " - calculate max value");
    }

    public void testReadFromFile() {
        p.drop();
        try {
            p.readAmountsFromFile("./", "amounts.txt");
            System.out.println("test " + ANSI_GREEN + "OK" + ANSI_RESET + " - read from file");
        } catch (IOException e) {
            System.out.println("test " + ANSI_RED + "FAILED" + ANSI_RESET + " - read from file");
        }
    }

    public static void main(String[] args) {
        TestPayments tl = new TestPayments();
        tl.testCalcMaxValue();
        tl.testCalcTotal();
        tl.testReadFromFile();
    }
}