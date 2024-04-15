/**
 * This main class uses the Fib class implemented using the Singleton 
 * creational design pattern
 */
public class MainFib {
    public static void main(String[] args) {
        Fib fib1 = Fib.getInstance();
        System.out.println("fib1: " + fib1.getValue());
        // fib2 contains the same instance as fib1
        Fib fib2 = Fib.getInstance();
        System.out.println("fib2: " + fib2.getValue());
    }
}
