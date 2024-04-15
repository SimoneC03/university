public interface IPaymentMethod {
    // generate token to create the payment request
    public String generateToken();

    // confirm payment request
    public boolean confirmPayment(String token);
}
