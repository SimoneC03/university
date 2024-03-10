#include <iostream>

using namespace std;

double toFahrenheit(double);
/* Return a given temperature value in Fahrenheit degrees */
double toFahrenheit(double n) {
    return (n * 9/5) + 32;
}

double toCelsius(double);
/* Return a given temperature value in Celsius degrees */
double toCelsius(double n) {
    return (n - 32) * 5/9;
}

int main() {
    cout << "Insert a temperature to convert (ex. 14 F)" << endl;
    string input;
    getline(cin, input);
    string delimiter = " ";
    string temperature = input.substr(0, input.find(delimiter));
    string symbol = input.substr(input.find(delimiter)+1, input.length());
    double temp = atof(temperature.c_str());
    if(symbol.compare("C") == 0 || symbol.compare("c") == 0) {
        double converted = toFahrenheit(temp);
        cout << "The converted temperature in Fahrenheit degrees is:  " << converted << " F" << endl;
    } else if(symbol.compare("F") == 0 || symbol.compare("f") == 0) {
        double converted = toCelsius(temp);
        cout << "The converted temperature in Celsius degrees is:  " << converted << " C" << endl;
    } else {
        cout << "Invalid symbol \"" << symbol << "\"." << endl;
        cout << "Supported temperature symbols are C and F." << endl;
    }
    return 0;
}