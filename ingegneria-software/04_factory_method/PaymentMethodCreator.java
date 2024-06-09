public class PaymentMethodCreator {
    public static IPaymentMethod getPaymentMethod(String apiSecret) {
        if(apiSecret.indexOf("paypal_") != -1) return new PayPal(apiSecret);
        else return new Stripe(apiSecret);
    }
}
