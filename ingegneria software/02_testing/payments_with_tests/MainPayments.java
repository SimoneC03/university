import java.io.IOException;

public class MainPayments {
    public static void main(String args[]) {
        Payments payments = new Payments();
        try {
            payments.readAmountsFromFile("./", "amounts.txt");
        } catch(IOException e) {
            System.out.println("An error has occurred while reading from the file: " + e);
        }
        
        payments.calcTotal();
        System.out.println("The total amount is: " + payments.getTotal());
    }
}
