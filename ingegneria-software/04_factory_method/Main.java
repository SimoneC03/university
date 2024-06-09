public class Main {
    public static void main(String args[]) {
        IPaymentMethod paymentProcessor = PaymentMethodCreator.getPaymentMethod("paypal_erfbidsfdsf222w2342jb");
        String tok = paymentProcessor.generateToken();
        if(paymentProcessor.confirmPayment(tok)) {
            System.out.println("The payment has been confirmed sucessfully (token: "+ tok +")");
        } else {
            System.out.println("An error has occurred while confirming the payment");
        }
    }
    
}
