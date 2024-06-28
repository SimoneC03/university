> This prorgam is not memory safe and it's created for learning purpose only. 

1. The server send a list of all the stored products like the following:
```
ID_product_1, Prod_name, Price, Qty_1
ID_product_2, Prod_name, Price, Qty_2
...
ID_product_N, Prod_name, Price, Qty_N
```

2. The client will send the server a string containing the chosen product like this:
```
ID_product, Qty
```
3. The server will generate a random id and a random qty different from those chosen by the user and will return the new random product to the client and update its stored quantity.
4. The client can insert the character “c” to continue (from the 1rst step) or “q” to end the purchase and the communication.


TCP socket and ipv6 addresses are required