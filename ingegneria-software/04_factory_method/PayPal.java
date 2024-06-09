public class PayPal implements IPaymentMethod {
    private String secret_api_token;

    public PayPal(String apiSecret) {
        secret_api_token = apiSecret;
    }

    // generate a random token to create the payment request
    @Override
    public String generateToken() {
        String random = "";
        for(int i=0; i<18; i++) {
            random += (char)(((Math.random() * 10000) % (122-30)) + 30);
        }
        return "paypal_"+random;
    }

    // confirm payment request
    @Override
    public boolean confirmPayment(String token) {
        return (token.indexOf("paypal_") != -1);
    }
}
