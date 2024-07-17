A generic client will send an Outfit packet to the Outfit server in order to perform one of the following operations:
1. Request the list of available dresses (including sizes and price)
2. Purchase one or more dresses (also choosing the quantity)
3. Return a dress (updating the list of available dresses)
4. Conclude the operation (when the client sends the word “END” the connection will be made deleted and the client process will terminate its execution)

For operation number 2 and 4 the server, in addition to sending the list of chosen clothes (with all the
details listed above), will also send you the message “Are you sure you want
do you confirm the operation?”. If the client responds with “Yes” then the server will respond with
“Operation completed” message, otherwise if the response is “No” the server will send the
“Operation cancelled” message and the customer can choose again one of the 4 operations listed previously.