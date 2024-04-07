/*
 * This class is implemented using the Singleton creational design pattern where
 * a class can be instantiated only once during the execution of the program
 */
public class Fib {
    private final static Fib obj = new Fib();
    private final int[] values = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    private int i;
    
    /* Private constructor that doesn't allow the instantiation through the
     * `new` keyword at the compiler level  */
    private Fib() {
        i = 0;
    }

    /* Return the same first instance */
    public static Fib getInstance() {
        return obj;
    }

    public int getValue() {
        if(i < 11) {
            i++;
        }
        return values[i - 1];
    }

    public void revert() {
        i = 0;
    }
}