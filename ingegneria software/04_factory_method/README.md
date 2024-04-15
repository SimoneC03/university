This is a dummy example to show the power of the Factory Method creational pattern and shall not be used for professional purposes.

The pattern comprehends different files with different roles:
- `IPaymentMethod` is the **Product**. The common interface to its various implementations;
- `PayPal` and `Stripe` are **ConcreteProduct**. Specific implementations of the Product.
- `PaymentMethodCreator` is the **Creator** or **ConcreteCreator** (implemented in one single file). It contains the Factory method that creates and returns *IPaymentMethod* objects.
- `Main` represents the Client which knows only the *IPaymentMethod* interface.